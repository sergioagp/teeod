  <h1 align="center">TEEOD</h1>
  <p align="center">Trusted Execution Environments On-Demand via Reconfigurable FPGA
    <br />
    <a href="https://youtu.be/ArsOXOTzKNM">View Demo</a>
    ·
    <a href="https://github.com/sergioagp/teeod/issues">Report Bug</a>
    ·
    <a href="https://github.com/sergioagp/teeod/issues">Request Feature</a>
  </p>
</p>



<!-- TABLE OF CONTENTS -->
<details open="open">
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgements">Acknowledgements</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About

Security is becoming paramount for IoT end-to-end solution designs. One well-established strategy to provide increased integrity and confidentiality for applications, from the edge to the cloud, is to rely on Trusted Execution Environments (TEE). One of the most common TEE design approaches is to create a virtual secure processor in the main application processor by leveraging specific security-oriented hardware extensions. Another approach that has also been taken by industry to provide a TEE is to use dedicated external secure elements. However, both of these approaches yield different weaknesses.

In this project, we introduce a novel TEE design aiming at disrupting the way TEEs are currently being built and deployed. We propose a newly refined TEE approach, named Trusted Execution Environments On-Demand (TEEOD), which leverages reconfigurable FPGA technology to provide additional security guarantees for security-critical applications. TEEOD approach implements secure enclaves in the programmable logic (PL) by instantiating a customized and dedicated security processor per application on a per-need basis.

### Built With
* [Vivado 2020.1](https://www.xilinx.com/support/download.html)
* [PetaLinux 2020.1](https://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/embedded-design-tools.html)
* [Cortex-M1](https://developer.arm.com/ip-products/designstart/fpga)

<!-- GETTING STARTED -->
## Getting Started

1. First open Vivado and select  `Tools -> Run Tcl Script...` and selecting the `<project_dir>/hw/project_teeod.tcl`
2. Generate bitstream.
3. Using the generated bitstream, build petalinux following this [Guide](https://www.96boards.org/documentation/consumer/ultra96/ultra96-v1/build/peta-linux.md.html).
4. After succesfully build linux, it's time to generate the host and the TA applications. First, genereate the teeodc libray, by running the Makefile in client-api folder.
5. Run the Makefile that is inside the folder apps/bitcoin-wallet you should obtain an bitcoin_wallet.elf (client application) and an TA.bin.
6. Copy the wallet and the TA.bin to any folder in choose inside the petalinux running on the Ultra96v2
7. Run the follow commands:
  ```sh
  ./wallet 1 1234                 #check if there is a master key run
  ./wallet 2 1234                 #generate a new master key
  ./wallet 3 1234 -a <mnemonic>   #generate a new master key from a mnemonic
  ./wallet 4 1234                 #erase the generated master key
  ./wallet 5 1234 -a <account_id> #sign a transaction
  ./wallet 6 1234                 #get the bitcoin address
  ```
<!--### Prerequisites

This is an example of how to list things you need to use the software and how to install them.
* npm
  ```sh
  npm install npm@latest -g
  ```
-->
<!--
### Installation

1. Get a free API Key at [https://example.com](https://example.com)
2. Clone the repo
   ```sh
   git clone https://github.com/your_username_/Project-Name.git
   ```
3. Install NPM packages
   ```sh
   npm install
   ```
4. Enter your API in `config.js`
   ```JS
   const API_KEY = 'ENTER YOUR API';
   ```
-->


<!-- USAGE EXAMPLES -->
## Usage

Use this space to show useful examples of how a project can be used. Additional screenshots, code examples and demos work well in this space. You may also link to more resources.

_For more examples, please refer to the [Documentation](https://github.com/sergioagp/teeod/tree/master/Documentation)_



<!-- ROADMAP -->
## Roadmap

See the [open issues](https://github.com/sergioagp/teeod/issues) for a list of proposed features (and known issues).

<!-- CONTACT -->
## Contact

Sérgio Pereira - [@Linkedin](https://www.linkedin.com/in/sergioagp/) - sergio.pereira@dei.uminho.pt
