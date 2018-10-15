// VUT FIT 3BIT
// ISA 2018/2019
// Project: Programovani sitove sluzby
// Variant: 2 - Export DNS informaci pomoci protokolu Syslog
// Author: Vladimir Dusek, xdusek27
// Date: 30/9/2018
// File: pcap_parser.h

#pragma once

#include <string>
#include <pcap/pcap.h>
#include <unordered_map>

extern pcap_t *handle;
extern std::unordered_map<std::string, int> result_map;

enum TypeDnsRecord {
    DNS_A = 1,
    DNS_AAAA = 28,
    DNS_CNAME = 5,
    DNS_DNSKEY = 48, // (dnssec) ToDo
    DNS_DS = 43, // (dnssec) ToDo
    DNS_MX = 15,
    DNS_NS = 2,
    DNS_NSEC = 47, // (dnssec) ToDo
    DNS_PTR = 12,
    DNS_RRSIG = 46, // (dnssec) ToDo
    DNS_SOA = 6,
    DNS_SPF = 99,
    DNS_TXT = 16
    // ToDo: vice typu
};

enum DnsSecAlgorithmType {
    DNSSEC_DELETE = 0,
    DNSSEC_RSAMD5 = 1,
    DNSSEC_DH = 2,
    DNSSEC_DSA = 3,
    DNSSEC_RSASHA1 = 5,
    DNSSEC_DSA_NSEC3_SHA1 = 6,
    DNSSEC_RSASHA1_NSEC3_SHA1 = 7,
    DNSSEC_RSASHA256 = 8,
    DNSSEC_RSASHA512 = 10,
    DNSSEC_ECC_GOST = 12,
    DNSSEC_ECDSAP256SHA256 = 13,
    DNSSEC_ECDSAP384SHA384 = 14,
    DNSSEC_ED25519 = 15,
    DNSSEC_ED448 = 16,
    DNSSEC_INDIRECT = 252,
    DNSSEC_PRIVATEDNS = 253,
    DNSSEC_PRIVATEOID = 254
    // Other values are reserved or unassigned
};

struct __attribute__((packed)) dns_header_t {
    u_int16_t id;
    u_int16_t flags;
    u_int16_t qd_count;
    u_int16_t an_count;
    u_int16_t ns_count;
    u_int16_t ar_count;
};

// Bytes are already in network ordering, there's no need for ntohs()
struct __attribute__((packed)) dns_header_flags_t {
    char rd :1;                // recursion desired
    char tc :1;                // truncated message
    char aa :1;                // authoritive answer
    char opcode :4;            // purpose of message, 0 for standard query
    char qr :1;                // query (0) / response (1) flag
    char rcode :4;             // response code, 0 if no error occurred
    char z :3;                 // not used, reserved for the future
    char ra :1;                // recursion available
};

struct __attribute__((packed)) dns_query_t {
    // + name of the node whose resource records are being requested
    u_int16_t type;
    u_int16_t class_;
};

struct __attribute__((packed)) dns_rr_t {
    // + encoded name of the node to which this resource record applies
    u_int16_t type;
    u_int16_t class_;
    u_int32_t ttl;
    u_int16_t data_len;
    // + specific record data
};

struct __attribute__((packed)) dns_rd_mx_t {
    int16_t preference;
    // exchange
};

struct __attribute__((packed)) dns_rd_soa_t {
    // + mname
    // + rname
    u_int32_t serial;
    int32_t refresh;
    int32_t retry;
    int32_t expire;
    u_int32_t minimum;
};

struct __attribute__((packed)) dns_rd_rrsig_t {
    u_int16_t type_covered;
    u_char algorithm;
    u_char labels;
    u_int32_t original_ttl;
    u_int32_t signature_expiration;
    u_int32_t signature_inception;
    u_int16_t key_tag;
    // + Signer's Name
    // + Signature
};

void packet_handler(u_char *args, const struct pcap_pkthdr *packet_hdr, const u_char *packet);

std::string dns_record_to_str(TypeDnsRecord type_dns_record);

std::string dnssec_algorithm_to_str(DnsSecAlgorithmType dnssec_algorithm_type);

std::string read_domain_name(u_char *dns_hdr, u_char *dns, u_int32_t *shift);

std::string read_ipv4(u_char *dns_reader);

std::string read_ipv6(u_char *dns_reader);

std::string read_soa(u_char *dns_hdr, u_char *dns);

std::string read_mx(u_char *dns_hdr, u_char *dns);

std::string read_txt(u_char *dns);

std::string read_nsec(u_char *dns_hdr, u_char *dns);

std::string read_rrsig(u_char *dns_hdr, u_char *dns, u_int16_t data_len);




class PcapParser {
private:
    std::string m_filename;
    std::string m_interface;

public:
    /**
     * Constructor.
     */
    PcapParser(std::string filename, std::string interface);

    /**
     * Destructor.
     */
    ~PcapParser();

    /**
     * Parse pcap file.
     */
    void parse_file();

    /**
     * Parse pcap file.
     */
    void parse_interface(u_int timeout);
};
