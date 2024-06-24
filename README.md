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

Tổng quan hệ thống:
![Picture8](https://github.com/nnnguyen1604/IOT_SmartStreetLight/assets/124754446/14d5daa7-fe80-4158-879d-85a71770ee85)


![Screenshot 2024-06-17 134809](https://github.com/nnnguyen1604/IOT_SmartStreetLight/assets/124754446/4d50aafe-b4a3-47ba-9253-21ab5f543ac8)


![Picture5](https://github.com/nnnguyen1604/IOT_SmartStreetLight/assets/124754446/cd29fe77-2643-49bd-aacc-ba3887ffa290)


Demo hoạt động 

![Screenshot (346)](https://github.com/nnnguyen1604/IOT_SmartStreetLight/assets/124754446/5a44920e-fff6-44ae-99e9-eaeff27fe3f6)


![Screenshot (346)](https://github.com/nnnguyen1604/IOT_SmartStreetLight/assets/124754446/cff3c740-e02a-4f50-9ef9-6bdd23e81ac8)
![Picture6](https://github.com/nnnguyen1604/IOT_SmartStreetLight/assets/124754446/7d31d90c-d0a1-449d-8cf8-118520a9dfac)

![Web_Photo_Editor](https://github.com/nnnguyen1604/IOT_SmartStreetLight/assets/124754446/22e5ade6-2217-44cf-b2ff-095b8286f6e3)
