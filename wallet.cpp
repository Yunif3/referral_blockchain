#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Token {
    string giver_hash;
    int num_use;
};

class Wallet {
private:
    string private_hash;
    string encoding_hash;
    vector<Token> token_collection;
    vector<Wallet> token_request_list;
    int given_token_count;

    void add_request (Wallet &owner) {
        if (was_token_requested(*this)) {
            owner.token_request_list.push_back(*this);
        }
    }

    void add_token (const Token t) {
        token_collection.push_back(t);
    }

    bool was_token_requested (Wallet &w) {
        vector<Wallet>::iterator it;
        it = find(begin(token_request_list), end(token_request_list), w);
        return it != end(token_request_list);
    } 

    void remove_request (Wallet &w) {
        vector<Wallet>::iterator it;
        it = find(begin(token_request_list), end(token_request_list), w);
        token_request_list.erase(it);
    }
public:
    void request_token(Wallet &owner) {
        add_request(owner);
        //TODO add a ledger to the blockchain
    }

    void give_token (Wallet &receiver, int allowed_use) {
        Token t;
        t.giver_hash = private_hash + encoding_hash;
        t.num_use = allowed_use;
        receiver.add_token(t);
        if (was_token_requested(receiver)) {
            remove_request(receiver);
        }
        given_token_count++;
        //TODO add a ledger to the blockchain
        //TODO send a message to the requester that he got the token
    }

    void decline_token (Wallet &requester) {
        remove_request(requester);
    } 

    int get_given_token_count () {
        return given_token_count;
    }

    int get_owned_token_count () {
        return (int) token_collection.size();
    }

};