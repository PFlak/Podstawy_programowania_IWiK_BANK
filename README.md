# Podstawy_programowania_IWiK_BANK
## Environment
+ Visual Studio 2022
+ Cmake 3.8
+ vcpkg
+ crow.h
+ sqlite3

## Architecture
### API
Our API is based on the CROW library and is deployed on the local network, accessible through port 18080.
The integration with CROW provides efficient routing, middleware support, and robust error handling.
Users can interact with the API via http://localhost:18080

Methods:
+/api/create_user
+/api/login_user
+/api/logout_user
+/api/check_balance