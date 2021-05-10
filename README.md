# Installation

## Dependencies
Dependencies will differ based on your platform, but the core library used in bleedr is libpcap (pcap). Unix based systems (including MacOS) will only need to install lex and bison, however Windows systems will need the windows version of lex and bison, as well as npcap - which serves as a wrapper around libpcap. 

### Windows
#### Dependencies
* npcap needs to be downloaded and installed: https://nmap.org/npcap/
* Win flex-bison needs to be downloaded and installed: https://github.com/lexxmark/winflexbison

### Unix/Mac
#### Dependencies

* Unix lex-bison needs to be downloaded and installed. For example, for apt ```sudo apt-get install bison flex```

## Executing (TODO)

To execute bleedr, simply navigate to the root of the bleedr directory and run the following. These commands will be the same, regardless of the system you are on. Dependencies must be installed (platform dependent) before these commands are run. 

* ```git submodule update --init``` (clones libpcap)
* ```cmake -B ./build -S .```



# Example JSON

```json
"data": [
  "packet1": {
   "link_layer": {
      "ether_type": "802.3",
      "source_mac": "A2:BE:1C:F3",
      "destination_mac": "FF:FF:FF:FF"
    },
   "network_layer": {
      "protocol": "ipv4",
      "source_ip": "192.168.1.10",
      "destination_ip": "35.231.233.15"
    },
   "transport_layer": {
      "protocol": "tcp",
      "source_port": "5232",
      "destination_port": "443"
    },
    "application_layer": {
    "protocol": "tls",
      "version": "1.3"
    },
  },
  "packet2": {}
]
```

This is likely to change, but this is the rough idea. Bleedr_t will open a write_file handle to a JSON write_file and write into the data array as each packet comes through. 