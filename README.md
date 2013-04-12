simodbus
========

A modbus master/slave simulator

Features

1. A windows desktop application

2. Coded in C++ using .NET 

3. Option to simulate a master or a slave.

4. Option to use serial port or TCP   ( TCP NYI )

5. Option to use ASCII or RTU mode

6. Able to configure serial port number

7. Able to configure TCP address and port number   ( NYI )

8. All slaves are assumed to be on the same port

9. Able to configure station numbers and register numbers that the slave will simulate.  ( NYI )

10. Able to send a read query to a specified station and register. 
    Value returned will be decoded and displayed.
    
11. Able to send a write query to a specified station and register with a specified value.  ( NYI )

12. Display log of all communications sent and received

13. Load configuration from or save to file.   ( NYI )