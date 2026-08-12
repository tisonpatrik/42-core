*This project has been created as part of the 42 curriculum by ptison.*

# NetPractice

## Description

NetPractice is a networking exercise focused on understanding and configuring small TCP/IP networks.

The project contains 10 levels with different network topologies. Each level requires fixing incorrect or incomplete network configurations so that the required hosts can communicate successfully.

The main concepts covered include:

* IPv4 addressing
* TCP/IP networking
* Subnet masks and CIDR notation
* Network and broadcast addresses
* Default gateways
* Routing tables
* Routers
* Switches
* Subnetting
* OSI model basics
* Communication between local and remote networks

The goal of the project is not to implement networking software, but to understand how network addressing and routing work and to be able to solve networking configurations manually.

## Instructions

### Running NetPractice

Extract the NetPractice files and run:

```bash
./run.sh
```

The script starts a local web server and opens the training interface in a web browser.

If `run.sh` does not work, the interface can be started manually:

```bash
python3 -m http.server 49242
```

Then open:

```text
http://localhost:49242
```

Enter your 42 login in the interface before solving the levels.

### Solving levels

There are 10 training levels.

For each level:

1. Modify the editable IP addresses, subnet masks, gateways and routes.
2. Use **Check again** to validate the configuration.
3. When the level is completed successfully, use **Get my config** to export the configuration.
4. Keep one exported configuration file for each level.

During the evaluation, random networking configurations must also be solved manually without external networking tools.

## Submission

The repository must contain:

* `README.md`
* 10 exported configuration files
* One configuration file for each of the 10 NetPractice levels

All 10 configuration files must be placed directly at the root of the repository.

## Resources

The following resources were used to study networking fundamentals and subnetting:

* [Crash Course Computer Science – Computer Networks](https://www.youtube.com/watch?v=3QhU9jd03a0&list=PL8dPuuaLjXtNlUrzyH5r6jN9ulIgZBpdo&index=31)
* [NetworkChuck – Networking fundamentals](https://www.youtube.com/watch?v=5WfiTHiU4x8&list=PLIhvC56v63IKrRHh3gvZZBAGvsvOhwrRF)
* [Samuraj.cz – TCP/IP addresses, masks, subnets and calculations](https://www.samuraj-cz.com/clanek/tcpip-adresy-masky-subnety-a-vypocty/)
* [caroldaniel/42sp-cursus-netpractice](https://github.com/caroldaniel/42sp-cursus-netpractice)

Topics studied using these resources included TCP/IP addressing, IPv4 addresses, subnet masks, CIDR notation, subnetting, network and broadcast addresses, default gateways, routing tables, routers, switches and the OSI model.

### AI Usage

AI was used as a learning and explanation aid while working on the project.

It was mainly used to:

* help identify mistakes in manually designed network configurations,
* help prepare this README, esspecially with proper english grammar.

The actual NetPractice configurations were solved and verified using the provided training interface.

