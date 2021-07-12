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

## Description of archive

    ```
  ├── apps
│   └── bitcoin-wallet			#folder that contains both the client application and the trusted application
│       ├── Android.mk
│       ├── CMakeLists.txt
│       ├── host			#folder that contains the client application
│       │   ├── include
│       │   │   ├── main.h
│       │   │   └── tx.h
│       │   ├── main
│       │   ├── main.c
│       │   ├── Makefile
│       │   ├── tx.c
│       │   └── wallet
│       ├── Makefile
│       └── ta				#folder that contains the trusted application
│           ├── bitcoin_wallet_ta.c
│           ├── bitcoin_wallet_ta.o
│           ├── include
│           │   └── bitcoin_wallet_ta.h
│           ├── Makefile
│           ├── sub.mk
│           └── user_ta_header_defines.h
├── client-lib				#folder that contains the TEE Client API
│   ├── contiguousMalloc.c
│   ├── include
│   │   ├── cma_malloc.h
│   │   ├── contiguousMalloc.h
│   │   ├── load_ta.h
│   │   ├── tee_client_api.h
│   │   ├── tee_defines.h
│   │   └── tee.h
│   ├── load_ta.c
│   ├── Makefile			# to generate the libteeodc.a
│   └── tee_client_api.c
├── hw					#folder that contains the hardware design
│   ├── ip_repo
│   │   ├── Arm_ipi_repository
│   │   ├── Arm_sw_repository
│   │   │   └── CortexM
│   │   ├── BRAM_loader_1.0
│   │   ├── security_monitor_1.0
│   │   └── tee_communication_agent_1.0
│   ├── project_teeod.tcl
│   ├── src
│   │   └── Ultra96_V2_constraints_190430.xdc
│   └── vivado_project
└── ta-api				#folder that contains the TEE Internal Core API
    ├── arch
    │   ├── cortex-m1
    │   │   ├── core_cm1.h
    │   │   └── linker.ld
    │   ├── newlib.c
    │   └── platform.h
    ├── entry.S
    ├── libutee
    │   ├── include
    │   │   ├── tee_api_defines.h
    │   │   ├── tee_api.h
    │   │   ├── tee_api_types.h
    │   │   ├── tee_internal_api_extensions.h
    │   │   ├── tee_internal_api.h
    │   │   └── tee_ta_api.h
    │   ├── tee_api.c
    │   ├── tee_api_objects.c
    │   └── tee_api_operations.c
    ├── Makefile
    ├── mk
    │   └── ta_dev_kit.mk		# called by the trusted application to generate the TA binary
    ├── tee.c
    ├── tee_isr.h
    ├── tee_isr.o
    ├── tee_isr.S
    └── tools
        └── bintocoe.py

    ```

<!-- GETTING STARTED -->
## Getting Started

This is an example of how you may give instructions on setting up your project locally.
To get a local copy up and running follow these simple example steps.

<!--### Prerequisites

This is an example of how to list things you need to use the software and how to install them.
* npm
  ```sh
  npm install npm@latest -g
  ```
-->

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



<!-- USAGE EXAMPLES -->
## Usage

Use this space to show useful examples of how a project can be used. Additional screenshots, code examples and demos work well in this space. You may also link to more resources.

_For more examples, please refer to the [Documentation](https://github.com/sergioagp/teeod/tree/master/Documentation)_



<!-- ROADMAP -->
## Roadmap

See the [open issues](https://github.com/othneildrew/Best-README-Template/issues) for a list of proposed features (and known issues).

<!-- CONTACT -->
## Contact

Sérgio Pereira - [@Linkedin](https://www.linkedin.com/in/sergioagp/) - sergio.pereira@dei.uminho.pt
