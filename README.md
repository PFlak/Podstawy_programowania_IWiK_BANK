# Podstawy_programowania_IWiK_BANK
## Build With

* [![VS][vs.dev]][vs-url]
* [![VS][cmake.dev]][cmake-url]
* [![VS][crow.dev]][crow-url]
* [![VS][vcpkg.dev]][vcpkg-url]
* [![VS][sqlite.dev]][sqlite-url]
## Architecture
### API
Our API is based on the CROW library and is deployed on the local network, accessible through port 18080.
The integration with CROW provides efficient routing, middleware support, and robust error handling.
Users can interact with the API via http://localhost:18080

Methods:
+ /api/create_user
+ /api/login_user
+ /api/logout_user
+ /api/check_balance





<!-- MARKDOWN LINKS & IMAGES -->
[vs.dev]:https://img.shields.io/badge/Visual%20Studio-v1.0.2-purple?style=for-the-badge
[vs-url]:https://visualstudio.microsoft.com/pl/
[cmake.dev]:https://img.shields.io/badge/Cmake-v3.22%2B-brightgreen?style=for-the-badge
[cmake-url]:https://cmake.org
[vcpkg.dev]:https://img.shields.io/vcpkg/v/entt?style=for-the-badge
[vcpkg-url]:https://vcpkg.io/
[crow.dev]:https://img.shields.io/badge/Crow.H-v1.0+3-red?style=for-the-badge
[crow-url]:https://crowcpp.org/
[sqlite.dev]:https://img.shields.io/badge/sqlite-v3-yellow?style=for-the-badge
[sqlite-url]:https://www.sqlite.org/index.html
