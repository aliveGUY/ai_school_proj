# AI School Proj

Даний додаток використовує штучний інтелект для розпізнавання об'єктів на фотографіях. В основі його роботи лежить модель машинного навчання, створена за допомогою Clarifai API, яка навчена на обширному наборі зображень.

## Встановлення

Більш детально про налаштування пректу розписано [тут](https://medium.com/@ilyadubrivvin/tutorial-simple-image-detection-android-app-358a2c10bfb7).<br/>
Щоб встановити додаток, виконайте такі дії:

1. Ініціалізуйте проект:
```sh
gradle wrapper
```
2. Побудуйте проект для експорту:
```sh
./gradlew build
```
3. Запустіть емулятор:
```sh
emulator -avd MyDevice
```

4. Увімкніть логи:
```sh
adb logcat -s mainActivity:*
```
5. Побудуйте та встановіть проект на емулятор:
```sh
./gradlew installDebug
```
6. Відкрийте додаток на емуляторі:
```sh
adb shell am start -n com.example.myandroidapp/.MainActivity
```

## Використання

Щоб скористатися додатком, виконайте такі дії:

1. Відкрийте додаток.
2. Натисніть кнопку "CAPTURE PHOTO".
3. Наведіть камеру на об'єкт, який хочете розпізнати.
4. Натисніть кнопку затвора.

Додаток розпізнає об'єкт на фотографії та видасть результат у вигляді списку.

## Повідомлення про помилки

Якщо ви виявили помилку в додатку, будь ласка, повідомте про це розробникам. Ви можете зробити це, надішлюючи електронний лист на адресу info@aischoolproj.dev

Дякуємо за використання додатку!
