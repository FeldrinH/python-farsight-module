<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->

<h1 align="center">🔭 Farsight 🔭</h1>

#### A simple passive memory reader for Python which aims to retrieve information about League of Legends spectator games which the API does not provide. Ported to Python from https://github.com/floh22/native-farsight-module.

Farsight uses Memory Reading to get information that the Riot API does not expose. Riot's policy in the past has been to allow passive memory reading, which is exactly what this program does, but this may change at any time.
Use Farsight at your own risk. Anti Cheat does not ban for programs used during spectate, but it does however run while in a live game. Having Farsight open
during a live (non-spectate) game may lead to account bans incase checks to stop it from running fail for some reason. None have been reported so far and [League Broadcast](https://github.com/floh22/LeagueBroadcast) has used similar methods for around two years now.

---

<h2 align="center">Features </h2>


<p align="left">Each memory snapshot produces game state information the moment the snapshot was taken. Each snapshot includes the following:<p>

1. Game time
2. Next dragon type to spawn
3. List of Champions
4. List of Turrets
5. List of inhibitors
6. Misc game objects


<p align="left">Each game object currently has the following data:<p>

1. Health/Max Health
2. Mana/Max Mana
3. Position
4. Team
5. Unit Id
6. Display Name
7. Current Gold / Total Gold
8. Level / Experience

(7 and 8 player only)

If you need any extra unit information, create an issue in the form of a feature request. Feature requests should be made to the [upstream repo](https://github.com/floh22/native-farsight-module).
<p align="left">Not possible: Aggregate player stats: (Kills, Deaths, Assists, CS, Vision Score)<p>

---

<h2 align="center">Installation</h2>

Run `pip install git+https://github.com/FeldrinH/python-farsight-module.git@main` to install latest version.

Note: Installation requires Visual Studio Build Tools 2017 or newer with the C++ desktop development workload.

The library is tested on Python 3.10 and 3.11. Python 3.9 and 3.12+ *should* be supported, but are untested.

---

<h2 align="center">Offsets</h2>

Roughly every two weeks League of Legends updates and its memory layout changes slightly, so offsets must be updated.

This Python module uses offsets from https://github.com/floh22/native-farsight-module. See the [README](https://github.com/floh22/native-farsight-module#offsets) in that repository for more info.


---

<h2 align="center">Example</h2>

Example usage is provided in the example folder of this repo. It currently contains a very basic console logger which conntects and prints the snapshot to the console.


---

<!-- LICENSE -->
<h2 align="center">License</h2>

Distributed under the MIT License. See `LICENSE` for more information.

__This is a standalone project from Lars Eble. Riot Games does not endorse or sponsor this project.__

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/floh22/native-farsight-module.svg?style=for-the-badge
[contributors-url]: https://github.com/floh22/native-farsight-module/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/floh22/native-farsight-module.svg?style=for-the-badge
[forks-url]: https://github.com/floh22/native-farsight-module/network/members
[stars-shield]: https://img.shields.io/github/stars/floh22/native-farsight-module.svg?style=for-the-badge
[stars-url]: https://github.com/floh22/native-farsight-module/stargazers
[issues-shield]: https://img.shields.io/github/issues/floh22/native-farsight-module.svg?style=for-the-badge
[issues-url]: https://github.com/floh22/native-farsight-module/issues
[license-shield]: https://img.shields.io/github/license/floh22/native-farsight-module.svg?style=for-the-badge
[license-url]: https://github.com/floh22/native-farsight-module/blob/master/LICENSE
[donate-paypal]: https://img.shields.io/badge/Paypal-Donate-blueviolet?style=for-the-badge&logo=paypal
