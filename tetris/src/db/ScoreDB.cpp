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
        PlayerRecord record;
        record.name = extractValue(block, "name");
        record.games = stoi("0" + extractValue(block, "games"));
        record.highScore = stoi("0" + extractValue(block, "highScore"));
        record.highLevel = stoi("0" + extractValue(block, "highLevel"));
        record.lastMode = extractValue(block, "lastMode");
        
        if (record.lastMode.empty()) {
            record.lastMode = "Normal";
        }

        if (!record.name.empty()) {
            records.push_back(record);
        }
        position = end + 1;
    }
    return records;
}

void saveScores(vector<PlayerRecord>& records) {
    ofstream file(DB_FILE);
    file << "[\n";
    
    for (int i = 0; i < records.size(); i++) {
        file << "  { \"name\": \"" << records[i].name << "\",";
        file << " \"games\": " << records[i].games << ",";
        file << " \"highScore\": " << records[i].highScore << ",";
        file << " \"highLevel\": " << records[i].highLevel << ",";
        file << " \"lastMode\": \"" << records[i].lastMode << "\" }";
        
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
        if (records[i].name == name) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        PlayerRecord newRecord;
        newRecord.name = name;
        newRecord.games = 1;
        newRecord.highScore = score;
        newRecord.highLevel = level;
        newRecord.lastMode = mode;
        records.push_back(newRecord);
    } else {
        records[foundIndex].games++;
        records[foundIndex].lastMode = mode;
        
        if (score > records[foundIndex].highScore) {
            records[foundIndex].highScore = score;
        }
        if (level > records[foundIndex].highLevel) {
            records[foundIndex].highLevel = level;
        }
    }
    
    saveScores(records);
}
