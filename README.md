# dns-export

<!----------------------------------------------------------------------------->

- BUT FIT
- Network Applications and Network Administration (ISA)
- Programming network service

<!----------------------------------------------------------------------------->

## Reference

> [**Assignment**](assignment/assignment.pdf)<br>
> — Description of assignment and its variant (Czech)

> [**Documentation**](doc/doc.pdf)<br>
> — Documentation of the project solution (Czech)

> [**Manual**](man/man.png)<br>
> — Linux standard manual page

<!----------------------------------------------------------------------------->

## Launch

### dns-export
```
$ cd src/
$ make
$ ./dns-export [-r RESOURCE | -i INTERFACE] [-t TIMEOUT] [-s SERVER] [-h]
```

### Manual page
```
$ man -l man/dns-export.1
```

<!----------------------------------------------------------------------------->

## Dependencies

### Libpcap

#### Debian, Ubuntu
```
$ apt-get install libpcap-dev
```

#### Fedora, Centos
```
$ dnf install libpcap-devel
```

#### Linking
```
$ g++ source_files.cpp -lpcap
```

### Syslog

#### Install rsyslog
```
$ dns install rsyslog
```

#### Stop default syslog deamon
```
# service syslog stop
```

#### Configure

Edit configuration
```
# vim /etc/rsyslog.conf
```

Enable for UDP 514 - uncomment the following lines in the MODULES section
```
# Provides UDP syslog reception
# for parameters see http://www.rsyslog.com/doc/imudp.html
module(load="imudp") # needs to be done just once
input(type="imudp" port="514")
```

#### Restart
```
# service rsyslog restart
```

#### Look at syslog messages
```
# cat /var/log/messages
```

<!----------------------------------------------------------------------------->

## Sources

### Articles
- http://www.tcpdump.org/pcap.html
- https://eecs.wsu.edu/~sshaikot/docs/lbpcap/libpcap-tutorial.pdf
- https://www.devdungeon.com/content/using-libpcap-c#load-pcap-file
- https://www.binarytides.com/dns-query-code-in-c-with-linux-sockets/
- https://eecs.wsu.edu/~sshaikot/docs/lbpcap/libpcap-tutorial.pdf
- http://yuba.stanford.edu/~casado/pcap/section4.html
- http://www.firewall.cx/networking-topics/protocols/domain-name-system-dns/160-protocols-dns-query.html
- http://www.keyboardbanger.com/dns-message-format-name-compression/
- https://access.redhat.com/solutions/54363

### Documentation

#### Posix
- https://linux.die.net/man/3/
- http://pubs.opengroup.org/onlinepubs/9699919799/
- http://man7.org/linux/man-pages/man3/

#### Pcap library
- https://www.tcpdump.org/manpages/

#### Manual pages
- https://liw.fi/manpages/

### Standards

#### RFCs
- https://tools.ietf.org/html/rfc1035
- https://tools.ietf.org/html/rfc3596
- https://tools.ietf.org/html/rfc4034
- https://tools.ietf.org/html/rfc3164
- https://tools.ietf.org/html/rfc5424
- https://tools.ietf.org/html/rfc3339

#### IANA
- https://www.iana.org/assignments/dns-sec-alg-numbers/dns-sec-alg-numbers.xhtml
- https://www.iana.org/assignments/ds-rr-types/ds-rr-types.xhtml
- https://www.iana.org/assignments/dns-parameters/dns-parameters.xhtml

### Stackoverflow
- https://stackoverflow.com/questions/7565300/identifying-dns-packets
- https://stackoverflow.com/questions/1784136/simple-signals-c-programming-and-alarm-function
- https://stackoverflow.com/questions/4583386/listening-using-pcap-with-timeout
- https://stackoverflow.com/questions/21092415/force-c-structure-to-pack-tightly
- https://stackoverflow.com/questions/2602823/in-c-c-whats-the-simplest-way-to-reverse-the-order-of-bits-in-a-byte
- https://stackoverflow.com/questions/2283494/get-ip-address-of-an-interface-on-linux
- https://stackoverflow.com/questions/361363/how-to-measure-time-in-milliseconds-using-ansi-c

### Wikipedia
- https://en.wikipedia.org/wiki/Domain_Name_System
- https://en.wikipedia.org/wiki/Domain_Name_System_Security_Extensions
- https://en.wikipedia.org/wiki/List_of_DNS_record_types

### C, C++ libraries
- https://en.wikipedia.org/wiki/C%2B%2B_Standard_Library
- https://en.wikipedia.org/wiki/C_standard_library
- https://en.wikipedia.org/wiki/C_POSIX_library
