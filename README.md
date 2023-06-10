# Global Money Depository -  Bank Papieski
<a name="readme-top"></a>
## About The Project
Made for University Project.
Expected features were:
* Class Polymorphic 
* Class Inheritance
* Abstract Class
* Inner Class
* It supposed to be based on C++
* App is supposed to show work in dedicated GUI or console
* It needs to save some kind of data to txt file

As a group we decide to go above and beyond to make it as great as possible with our limited work group
and made features like:
* Dedicated Gui
* Admin account to manage users
* Option to own multiple wallets in one account (in project its set up as max 3 for sake of presentation)


### Build With

* [![VS][vs.dev]][vs-url]
* [![VS][cmake.dev]][cmake-url]
* [![VS][crow.dev]][crow-url]
* [![VS][vcpkg.dev]][vcpkg-url]
* [![VS][sqlite.dev]][sqlite-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Getting Started
With this quick tutorial we help we can guide you with instalation and startup

### Prerequisites
To even start instalation process you need to have nodeJS

[![VS][node.dev]][node-url]
### Installation


1. Clone the repo
 
 ```sh
   git clone https://github.com/PFlak/Podstawy_programowania_IWiK_BANK
   ```

2. Install Angular packages
 
  ```sh
  npm install -g @angular/cli@15.0.4
   ```

3. Start Server

   ```js
    ng serve
   ```
4. Go to http://localhost:18080 to access your bank app


<p align="right">(<a href="#readme-top">back to top</a>)</p>

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

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Contributing
* Piotr Flak - [![flak][git.dev]][flak-url] [![flak2][linked.dev]][flak2-url]
* Miłosz Rzyczniak - [![milosz][git.dev]][milosz-url] [![milosz2][linked.dev]][milosz2-url]
* Marcin Gut-Borowy -  [![sars][git.dev]][sars-url]   [![sars2][linked.dev]][sars2-url] 
* Michał Kurzyński - [![michal][git.dev]][michal-url] [![michal2][linked.dev]][michal2-url]
* Krzysztof Broniak - [![broniak][git.dev]][broniak-url] [![broniak2][linked.dev]][broniak2-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
[git.dev]: https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white
[linked.dev]: https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white

[sars2-url]: https://www.linkedin.com/in/marcin-gut-borowy-4b4854203/
[milosz2-url]:  https://www.linkedin.com/in/mi%C5%82osz-rzyczniak-b68175253/
[flak2-url]: https://www.linkedin.com/in/krzysztof-broniak-2283b3246/
[michal2-url]: https://www.linkedin.com/in/krzysztof-broniak-2283b3246/
[broniak2-url]: https://www.linkedin.com/in/krzysztof-broniak-2283b3246/

[sars-url]: https://github.com/SARSUnicorn
[milosz-url]: https://github.com/Rzyczu
[flak-url]: https://github.com/PFlak
[michal-url]: https://github.com/Trejden
[broniak-url]:  https://github.com/SARSUnicorn

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

[node.dev]:https://img.shields.io/badge/Node.js-43853D?style=for-the-badge&logo=node.js&logoColor=white
[node-url]:https://nodejs.org/en
