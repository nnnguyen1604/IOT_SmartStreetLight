IOT SMART STREET LIGHT
-----------------------------------------------------------------------------------
Sortware: Arduino IDE

Hardware: Esp32, Arduino, Sensor light

Protocol: Lora 

Realtime Database: FrireBase

 --------------------------------------------------------------------------------
 ESP32:
   - Lấy các thông tin điều khiển từ Firebase dựa vào đường dẫn sau đó truyền đến các đèn.
   - Nhận thông tin từ các đèn tách biệt dựa vào ID sau đó đưa thông tin lên Firebase để quản lý.

Arduino: 
   - Tiếp nhận thông tin điều khiển của Esp32 điều khiển chế độ hoạt động, độ sáng. 
   - Truyền thông số cảm biến ánh sáng và báo lỗi đến ESP32 để xử lý.

Tổng quan hệ thống:

![Picture8](https://github.com/nnnguyen1604/IOT_SmartStreetLight/assets/124754446/14d5daa7-fe80-4158-879d-85a71770ee85)
![Presentation1](https://github.com/user-attachments/assets/760f1411-24bb-436e-8e6e-fb5d261607f4)


![gateway vpd (3)](https://github.com/user-attachments/assets/8c757911-14d3-4989-a743-4c5b86d1c08f)

![gateway vpd (4)](https://github.com/user-attachments/assets/514e45f1-d931-4e4a-9459-130d05a05f21)



![Picture5](https://github.com/nnnguyen1604/IOT_SmartStreetLight/assets/124754446/cd29fe77-2643-49bd-aacc-ba3887ffa290)


Demo hoạt động 
![Screenshot 2024-07-17 010803](https://github.com/user-attachments/assets/74e56fc7-1c31-4640-805d-17e6df521b6a)
![Screenshot 2024-07-17 010811](https://github.com/user-attachments/assets/4bc2ad97-de6a-4faa-927f-7324f25d4f91)


![Screenshot (346)](https://github.com/nnnguyen1604/IOT_SmartStreetLight/assets/124754446/cff3c740-e02a-4f50-9ef9-6bdd23e81ac8)


![Screenshot 2024-07-17 010819](https://github.com/user-attachments/assets/702e85bd-9ffd-45c9-a6e6-d3ed5a351dc9)

