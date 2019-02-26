#ifndef ZCOIN_NEXTGENPROOF_H
#define ZCOIN_NEXTGENPROOF_H

#include "SchnorrProof.h"
#include "RangeProof.h"
#include "Params.h"

using namespace secp_primitives;

namespace nextgen{

class NextGenProof {
public:
    //n is the number of input coins, bulletproof_n is number of output coins,
    inline int memoryRequired(int n, int bulletproof_n, int bulletproof_m) {
        sigma_proofs[0].memoryRequired() * n
        + bulletproofs.memoryRequired(bulletproof_n, bulletproof_m)
        + schnorrProof.memoryRequired();
    }
    inline unsigned char* serialize(unsigned char* buffer) const {
        unsigned char* current = buffer;
        for(int i = 0; i < sigma_proofs.size(); ++i)
            current = sigma_proofs[i].serialize(current);
        current = bulletproofs.serialize(current);
        return schnorrProof.serialize(current);
    }
    inline unsigned char* deserialize(const Params* params, unsigned char* buffer, int size) {
        unsigned char* current = buffer;
        for(int i = 0; i < size; ++i)
            current = sigma_proofs[i].deserialize(current, params->get_n(), params->get_m());
        current = bulletproofs.deserialize(current);
        return schnorrProof.deserialize(current);
    }

    std::vector<SigmaPlusProof<Scalar, GroupElement>> sigma_proofs;
    RangeProof<Scalar, GroupElement> bulletproofs;
    SchnorrProof<Scalar, GroupElement> schnorrProof;
};
}//namespace nextgen

#endif //ZCOIN_NEXTGENPROOF_H