### Init project

`gradle wrapper`

### Build project for export

`./gradlew build`

### Start emulator

`emulator -avd MyDevice`

### Turn on loggs

`adb logcat -s MainActivity:*`

### Build and install project on emulator

`./gradlew installDebug`


### Open applicatoins on emulator

`adb shell am start -n com.example.myandroidapp/.MainActivity`