#include "../../include/db/ScoreDB.h"
#include <fstream>

string DB_FILE = "db/scores.json";

string extractValue(string json, string key) {
    string search = "\"" + key + "\": ";
    int position = json.find(search);
    if (position == -1) return "";

    int start = position + search.size();
    int end = start;

    if (json[start] == '"') {
        start++;
        end = json.find('"', start);
        return json.substr(start, end - start);
    }

    while (end < json.size() && json[end] != ',' && json[end] != '}') {
        end++;
    }
    return json.substr(start, end - start);
}

vector<PlayerRecord> loadScores() {
    vector<PlayerRecord> records;
    ifstream file(DB_FILE);
    if (!file.is_open()) {
        return records;
    }

    string content = "";
    string line;
    while (getline(file, line)) {
        content += line;
    }
    file.close();

    int position = 0;
    while (true) {
        int start = content.find('{', position);
        int end = content.find('}', position);
        if (start == -1 || end == -1) {
            break;
        }

        string block = content.substr(start, end - start + 1);
        string rName  = extractValue(block, "name");
        int    rGames = stoi("0" + extractValue(block, "games"));
        int    rHS    = stoi("0" + extractValue(block, "highScore"));
        int    rHL    = stoi("0" + extractValue(block, "highLevel"));
        string rMode  = extractValue(block, "lastMode");
        if (rMode.empty()) rMode = "Normal";

        if (!rName.empty()) {
            records.push_back(PlayerRecord(rName, rGames, rHS, rHL, rMode));
        }
        position = end + 1;
    }
    return records;
}

void saveScores(vector<PlayerRecord>& records) {
    ofstream file(DB_FILE);
    file << "[\n";
    
    for (int i = 0; i < records.size(); i++) {
        file << "  { \"name\": \"" << records[i].getName() << "\",";
        file << " \"games\": " << records[i].getGames() << ",";
        file << " \"highScore\": " << records[i].getHighScore() << ",";
        file << " \"highLevel\": " << records[i].getHighLevel() << ",";
        file << " \"lastMode\": \"" << records[i].getLastMode() << "\" }";
        
        if (i < records.size() - 1) {
            file << ",";
        }
        file << "\n";
    }
    
    file << "]\n";
    file.close();
}

void updatePlayer(vector<PlayerRecord>& records, string name, int score, int level, string mode) {
    int foundIndex = -1;
    
    for (int i = 0; i < records.size(); i++) {
        if (records[i].getName() == name) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        records.push_back(PlayerRecord(name, 1, score, level, mode));
    } else {
        records[foundIndex].incrementGames();
        records[foundIndex].setLastMode(mode);
        records[foundIndex].updateHighScore(score);
        records[foundIndex].updateHighLevel(level);
    }
    
    saveScores(records);
}
