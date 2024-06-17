# IOT_SmartStreetLight
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
![Screenshot (346)](https://github.com/nnnguyen1604/IOT_SmartStreetLight/assets/124754446/4508ac35-841b-4f63-9d61-55fc4e009e82)
