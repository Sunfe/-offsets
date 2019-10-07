#ifndef ETHOFFSET_H
#define ETHOFFSET_H
#include "offset.h"

class EthOffset : public Offset
{
public:
    enum ETH_FRAME
    {
        ETH_FRAME_ETH2,
        ETH_FRAME_8023
    };

    EthOffset(qint8 type = ETH_FRAME_ETH2);
    ~EthOffset();

    void loadOffsetEth2();
    void loadOffsetEth8023();
    void appendOffsetIpField();
    void adjustRangeByteOffset(qint32 start, qint32 end, qint32 deltaOffset);
    void insertOffset8023qTag();

    virtual QString format();
    QString formatMacAddress(QString src);
    QString formatIpAddress(QString src);
    virtual void extractData();
private:
    bool isTagged;     /* conformed with ieee802.1q */
    qint32 protocal;  
                       /* 协议号，常见的列举如下：
                        * 0x0000   0x05DC      IEEE 802.3 长度
                        * 0x0101   0x01FF  实验
                        * 0x0600   XEROX NS IDP
                        * 0x0660
                        * 0x0661   DLOG
                        * 0x0800   网际协议（IP）
                        * 0x0801   X.75 Internet
                        * 0x0802   NBS Internet
                        * 0x0803   ECMA Internet
                        * 0x0804   Chaosnet
                        * 0x0805   X.25 Level 3
                        * 0x0806   地址解析协议（ARP ： Address Resolution Protocol）
                        * 0x0808   帧中继 ARP （Frame Relay ARP） [RFC1701]
                        * 0x6559   原始帧中继（Raw Frame Relay） [RFC1701]
                        * 0x8035   动态 DARP （DRARP：Dynamic RARP）反向地址解析协议（RARP：Reverse Address Resolution Protocol）
                        * 0x8037   Novell Netware IPX
                        * 0x809B   EtherTalk
                        * 0x80D5   IBM SNA Services over Ethernet
                        * 0x80F3   AppleTalk 地址解析协议（AARP：AppleTalk Address Resolution Protocol）
                        * 0x8100   以太网自动保护开关（EAPS：Ethernet Automatic Protection Switching）
                        * 0x8137   因特网包交换（IPX：Internet Packet Exchange）
                        * 0x814C   简单网络管理协议（SNMP：Simple Network Management Protocol）
                        * 0x86DD   网际协议v6（IPv6，Internet Protocol version 6）
                        * 0x8809   OAM
                        * 0x880B   点对点协议（PPP：Point-to-Point Protocol）
                        * 0x880C   通用交换管理协议（GSMP：General Switch Management Protocol）
                        * 0x8847   多协议标签交换（单播） MPLS：Multi-Protocol Label Switching <unicast>）
                        * 0x8848   多协议标签交换（组播）（MPLS, Multi-Protocol Label Switching <multicast>）
                        * 0x8863   以太网上的 PPP（发现阶段）（PPPoE：PPP Over Ethernet <Discovery Stage>）
                        * 0x8864   以太网上的 PPP（PPP 会话阶段） （PPPoE，PPP Over Ethernet<PPP Session Stage>）
                        * 0x88BB   轻量级访问点协议（LWAPP：Light Weight Access Point Protocol）
                        * 0x88CC   链接层发现协议（LLDP：Link Layer Discovery Protocol）
                        * 0x8E88   局域网上的 EAP（EAPOL：EAP over LAN）
                        * 0x9000   配置测试协议（Loopback）
                        * 0x9100   VLAN 标签协议标识符（VLAN Tag Protocol Identifier）
                        * 0x9200   VLAN 标签协议标识符（VLAN Tag Protocol Identifier）
                        * 0xFFFF   保留
                        */

};

#endif // ETHOFFSET_H
