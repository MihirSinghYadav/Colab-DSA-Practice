#include <bits/stdc++.h>
using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

// Normal Approach
vector<int> climbingLeaderboard(vector<int> ranked, vector<int> player) {
    vector<int> player_rank;
    int rank = 1;
    for(int i = 0; i < ranked.size() - 1; i++) {
        if(ranked[i] != ranked[i + 1]) {
            rank++;
        }
    }
    rank++;
    int j = ranked.size() - 1;
    for(int i = 0; i < player.size();) {
        if(ranked[j] == ranked[j - 1])
            j--;
        else if(player[i] >= ranked[j]) {
            if(rank > 1)
                rank--;
            j--;
        } else {
            player_rank.push_back(rank);
            i++;
        }
    }    
    return player_rank;

}

// Set Approach
vector<int> climbingLeaderboard_set(vector<int> leaderboard, vector<int> player) {
    set<int> rankSet(leaderboard.begin(), leaderboard.end());
    vector<int> player_rank;
    for(int score : player) {
        rankSet.insert(score);
        int rank = distance(rankSet.upper_bound(score), rankSet.end());
        player_rank.push_back(rank);
        rankSet.erase(score);
    }
    return player_rank;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string ranked_count_temp;
    getline(cin, ranked_count_temp);

    int ranked_count = stoi(ltrim(rtrim(ranked_count_temp)));

    string ranked_temp_temp;
    getline(cin, ranked_temp_temp);

    vector<string> ranked_temp = split(rtrim(ranked_temp_temp));

    vector<int> ranked(ranked_count);

    for (int i = 0; i < ranked_count; i++) {
        int ranked_item = stoi(ranked_temp[i]);

        ranked[i] = ranked_item;
    }

    string player_count_temp;
    getline(cin, player_count_temp);

    int player_count = stoi(ltrim(rtrim(player_count_temp)));

    string player_temp_temp;
    getline(cin, player_temp_temp);

    vector<string> player_temp = split(rtrim(player_temp_temp));

    vector<int> player(player_count);

    for (int i = 0; i < player_count; i++) {
        int player_item = stoi(player_temp[i]);

        player[i] = player_item;
    }

    // vector<int> result = climbingLeaderboard(ranked, player);
    vector<int> result = climbingLeaderboard_set(ranked, player);


    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
