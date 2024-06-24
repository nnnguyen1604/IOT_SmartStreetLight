IOT SMART STREET LIGHT
-----------------------------------------------------------------------------------
Sortware: Arduino IDE

Hardware: Esp32, Arduino, Sensor light

Protocol: Lora 

SQL: noSQL FireBase

 --------------------------------------------------------------------------------
 ESP32:
   - Lấy các thông tin điều khiển từ Firebase dựa vào đường dẫn sau đó truyền đến các đèn.
   - Nhận thông tin từ các đèn tách biệt dựa vào ID sau đó đưa thông tin lên Firebase để quản lý.

Arduino: 
   - Tiếp nhận thông tin điều khiển của Esp32 điều khiển chế độ hoạt động, độ sáng. 
   - Truyền thông số cảm biến ánh sáng và báo lỗi đến ESP32 để xử lý.

![Screenshot 2024-06-17 134809](https://github.com/nnnguyen1604/IOT_SmartStreetLight/assets/124754446/4d50aafe-b4a3-47ba-9253-21ab5f543ac8)

Demo hoạt động 

![Screenshot (346)](https://github.com/nnnguyen1604/IOT_SmartStreetLight/assets/124754446/5a44920e-fff6-44ae-99e9-eaeff27fe3f6)
![Screenshot (346)](https://github.com/nnnguyen1604/IOT_SmartStreetLight/assets/124754446/cff3c740-e02a-4f50-9ef9-6bdd23e81ac8)
![449053585_8114647801899493_1858334538978216483_n](https://github.com/nnnguyen1604/IOT_SmartStreetLight/assets/124754446/79867a5a-5368-49b5-8de6-d4f60a4221da)
![448373546_2638423506338451_3754061036794573936_n](https://github.com/nnnguyen1604/IOT_SmartStreetLight/assets/124754446/e3ff0b2b-82e8-433f-901f-98cbb8f1521c)
