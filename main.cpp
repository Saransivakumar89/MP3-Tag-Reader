#include<iostream>
#include<fstream>

using namespace std;

struct ID3 {
    char header[3];
    char version[2];
    char frameID[4];
};

class MP3 {
    string filename;
    ID3 tag;
    const char *frames[6] = {"TPE1","TIT2","TALB","TCOM","TCON","TDRC"}; 
    const char *tags[6] = {"ARTIST","TITLE","ALBUM","COMPOSER","COMMENT","YEAR"};
    fstream file; // Added file declaration

public:
    MP3(const string &filename): filename(filename) {}

    void readTag() {
        file.open(filename, ios::binary); 
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        file.read(tag.header, sizeof(tag.header));
        file.read(tag.version, sizeof(tag.version));
        file.read(tag.frameID, sizeof(tag.frameID));
        file.close();
    }

    void displayTag() {
        cout << "Tag Information:" << endl;
        cout << "Header: " << tag.header[0] << tag.header[1] << tag.header[2] << endl;
        cout << "Version: " << tag.version[0] << tag.version[1] << endl;

        for (int i = 0; i < 6; i++) {
            string val = getFrame(i);
            cout << tags[i] << ": " << val << endl;
        }
    }

private:
    string getFrame(int index) {
        const char* frameID = frames[index];
        for (int i = 0; i < 4; i++) {
            if (tag.frameID[i] != frameID[i])
                return "";
        }
        string value(tag.frameID + 4);
        return value;
    }
};

int main(int argc , char *argv[]) {
    if (argc < 2) {
        cerr << "Error: Insufficient arguments!" << endl;
        cerr << "Usage: " << argv[0] << " [-v | -e] <filename>" << endl;
        return -1;
    }

    string opt = argv[1];
    string filename = argv[2];

    if (filename.substr(filename.size() - 4) != ".mp3") {
        cerr << "Error: Not an MP3 file!" << endl;
        return -1;
    }

    MP3 reader(filename);

    if (opt == "-v") {
        reader.readTag();
        reader.displayTag();
    } else {
        cerr << "Error: Invalid option!" << endl;
        cerr << "Usage: " << argv[0] << " [-v | -e] <filename>" << endl;
        return -1;
    }

    return 0;
}


