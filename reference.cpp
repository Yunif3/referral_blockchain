#include <string>
#include <iostream>

using std::string;

struct Token {
    string hash;
};

class Reference {
    private:
        string giver;
        string giver_hash;
        string receiver_hash;
        string referral;
        int allowed_usage;

        // TODO
        void notify_giver () {
            return;
        }
        bool check_enough_allowed () {
            return allowed_usage > 0;
        } 

    public:
        Reference ()
            :giver(""), giver_hash(""), receiver_hash(""),
            referral(""), allowed_usage(0) {}
        
        Reference (string giv, string g_hash, string r_hash) 
            :giver(giv), giver_hash(g_hash), receiver_hash(r_hash),
            referral(""), allowed_usage(0) {}

        std::string retrieve_referral(Token t) {
            if (check_valid_token(t, receiver_hash) && check_enough_allowed()) {
                allowed_usage -= 1;
                notify_giver();
                return referral;
            }
            
            return "The referral is not accessible by this key";
        }

        void change_referral (string new_referral, string hash) {
            if (giver_hash == hash) { referral = new_referral; }
        }
        
        void increase_allowed_usage (int amount, std::string hash) {
            if (giver_hash == hash) { allowed_usage += amount; }
        }

        int check_allowed_usage () {
            return allowed_usage;
        }
};

bool check_valid_token (Token t, std::string hash) {
    if (t.hash == hash) { return true; }
    else {
        std::cerr << "wrong hash given. Invalid token";
        return false;
    }
}
