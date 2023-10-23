package com.example.myandroidapp;

import android.os.Bundle;
import android.util.Log;
import androidx.appcompat.app.AppCompatActivity;
import android.content.pm.PackageManager;
import android.content.Intent; // Import Intent
import android.graphics.Bitmap; // Import Bitmap
import android.graphics.BitmapFactory; // Import BitmapFactory
import android.provider.MediaStore;
import android.Manifest;

import android.util.Base64;
import java.io.ByteArrayOutputStream;
import com.google.protobuf.ByteString;

import io.grpc.ManagedChannel;
import io.grpc.ManagedChannelBuilder;
import io.grpc.Metadata;
import io.grpc.stub.MetadataUtils;
import io.grpc.StatusRuntimeException;

import com.clarifai.grpc.api.*;
import com.clarifai.channel.ClarifaiChannel;
import com.clarifai.credentials.ClarifaiCallCredentials;
import com.clarifai.grpc.api.status.StatusCode;

import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.view.View; // Import View
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import androidx.annotation.Nullable;

public class MainActivity extends AppCompatActivity {
    private static final int CAMERA_PERMISSION_REQUEST = 100;
    private static final int CAMERA_REQUEST = 101;

    private static final String TAG = "MainActivity";
    static final String PAT = "d36ad14f0cd344efbce2385a82f60581";
    static final String USER_ID = "clarifai";
    static final String APP_ID = "main";
    static final String MODEL_ID = "general-image-recognition";
    static final String MODEL_VERSION_ID = "aa7f35c01e0642fda5cf400f543e7c40";
    static final String IMAGE_URL = "https://samples.clarifai.com/MauricioMacri.jpg";
    static final String CONCEPT_NAME = "train";
    static final String CONCEPT_ID = "ai_6kTjGfF6";

    private Button captureButton;
    private ImageView photoImageView;
    private TextView textView;
    private TextView clarifaiResultTextView;

    V2Grpc.V2BlockingStub stub;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        captureButton = findViewById(R.id.captureButton);
        photoImageView = findViewById(R.id.photoImageView);
        textView = findViewById(R.id.textView);
        clarifaiResultTextView = findViewById(R.id.clarifaiResultTextView);

        if (ContextCompat.checkSelfPermission(this, Manifest.permission.CAMERA) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this, new String[] {
                    Manifest.permission.CAMERA },
                    CAMERA_PERMISSION_REQUEST);
        }

        captureButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                openCamera();
            }
        });

        // Build the gRPC channel
        ManagedChannel channel = ManagedChannelBuilder.forAddress("api.clarifai.com", 443)
                .useTransportSecurity()
                .build();

        // Create a stub for gRPC communication
        stub = V2Grpc.newBlockingStub(channel);

        // Define a request

    }

    private void openCamera() {
        // Check if camera permission is granted
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.CAMERA) != PackageManager.PERMISSION_GRANTED) {
            // Request permission if not granted
            ActivityCompat.requestPermissions(this, new String[] {
                    Manifest.permission.CAMERA },
                    CAMERA_PERMISSION_REQUEST);
        } else {
            // Camera permission is granted, proceed to open the camera
            textView.setText("Opening camera...");
            Intent cameraIntent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
            if (cameraIntent.resolveActivity(getPackageManager()) != null) {
                startActivityForResult(cameraIntent, CAMERA_REQUEST);
            }
        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == CAMERA_REQUEST && resultCode == RESULT_OK) {
            Bitmap photo = (Bitmap) data.getExtras().get("data");
            if (photo != null) {
                photoImageView.setImageBitmap(photo);
                photoImageView.setVisibility(View.VISIBLE);

                textView.setText("Photo taken, detecting objects...");
                detectObjectsInImage(photo);
            }
        }
    }

    private void detectObjectsInImage(Bitmap bitmap) {
        Log.d(TAG, "Button pressed");

        // Convert the Bitmap to a base64-encoded image
        ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
        bitmap.compress(Bitmap.CompressFormat.PNG, 100, byteArrayOutputStream);
        byte[] imageBytes = byteArrayOutputStream.toByteArray();
        String base64Image = Base64.encodeToString(imageBytes, Base64.DEFAULT);

        ByteString base64ByteString = ByteString.copyFrom(Base64.decode(base64Image, Base64.DEFAULT)); // Convert to
                                                                                                       // ByteString

        PostModelOutputsRequest request = PostModelOutputsRequest.newBuilder()
                .setUserAppId(UserAppIDSet.newBuilder().setUserId(USER_ID).setAppId(APP_ID))
                .setModelId(MODEL_ID)
                .setVersionId(MODEL_VERSION_ID) // This is optional. Defaults to the latest model version
                .addInputs(
                        Input.newBuilder().setData(
                                Data.newBuilder().setImage(
                                        Image.newBuilder().setBase64(base64ByteString)))) // Use the ByteString here
                .setModel(
                        Model.newBuilder().setOutputInfo(
                                OutputInfo.newBuilder().setOutputConfig(
                                        OutputConfig.newBuilder())))
                .build();

        Metadata metadata = new Metadata();
        metadata.put(Metadata.Key.of("Authorization", Metadata.ASCII_STRING_MARSHALLER), "Key " + PAT);

        stub = MetadataUtils.attachHeaders(stub, metadata);

        MultiOutputResponse response = stub.postModelOutputs(request);

        if (response.getStatus().getCode() == StatusCode.SUCCESS) {
            Log.d(TAG, "IS SUCCESS");
        } else {
            Log.d(TAG, "Response status is not SUCCESS");
        }

        Output output = response.getOutputs(0);

        String result = "";

        if (output.getData().getConceptsList() != null) {
            int conceptCount = output.getData().getConceptsList().size();
            Log.d(TAG, "Number of Concepts: " + conceptCount);

            for (Concept concept : output.getData().getConceptsList()) {
                Log.d(TAG, "Name => " + concept.getName());
                result += "\n" + concept.getName();
            }
        } else {
            Log.d(TAG, "Concepts list is null");
        }

        clarifaiResultTextView.setText(result);
    }

}
