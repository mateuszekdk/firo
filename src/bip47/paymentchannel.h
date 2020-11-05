#ifndef ZCOIN_BIP47CHANNEL_H
#define ZCOIN_BIP47CHANNEL_H
#include "bip47/address.h"
#include <string>
#include "serialize.h"
#include "streams.h"
#include "uint256.h"


class CWallet;

namespace bip47 {

class CPaymentChannel
{
public:
    CPaymentChannel();
    CPaymentChannel(string v_myPaymentCode, string v_paymentCode);
    CPaymentChannel(string v_myPaymentCode, string v_paymentCode, string v_label);

    string getPaymentCode() const;
    string getMyPaymentCode() const;
    void setPaymentCode(string pc);
    std::vector<CAddress> getIncomingAddresses() const;
    int getCurrentIncomingIndex() const;
    void generateKeys(CWallet* bip47Wallet);
    CAddress const * getIncomingAddress(string address) const;
    void addNewIncomingAddress(string newAddress, int nextIndex);
    string getLabel() const;
    void setLabel(string l);
    std::vector<string> getOutgoingAddresses() const;
    uint256 getNotificationTxHash() const;
    bool isNotificationTransactionSent() const;
    void setStatusSent(uint256 notiTxHash);
    int getCurrentOutgoingIndex() const;
    void incrementOutgoingIndex();
    void addAddressToOutgoingAddresses(string address);
    void setStatusNotSent();
    void addTransaction(uint256 hash);
    void getTransactions(std::vector<uint256>& hashes) const;

    ADD_SERIALIZE_METHODS;
    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action)
    {
        READWRITE(paymentCode);
        READWRITE(myPaymentCode);
        READWRITE(label);
        READWRITE(status);
        READWRITE(currentIncomingIndex);
        READWRITE(currentOutgoingIndex);
        READWRITE(incomingAddresses);
        READWRITE(outgoingAddresses);
        READWRITE(notiTxHash);
        READWRITE(transactions);
    }

private:
    static string TAG;

    static int STATUS_NOT_SENT;
    static int STATUS_SENT_CFM;
    static int LOOKAHEAD;
    string myPaymentCode;
    string paymentCode;
    string label;
    std::vector<CAddress> incomingAddresses;
    std::vector<string> outgoingAddresses;
    std::vector<uint256> transactions;
    int status;
    int currentOutgoingIndex;
    int currentIncomingIndex;
    uint256 notiTxHash;
};

}

#endif // ZCOIN_BIP47CHANNEL_H
