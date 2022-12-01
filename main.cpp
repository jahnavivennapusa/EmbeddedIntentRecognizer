#include <bits/stdc++.h>
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <vector>

using namespace std;


static vector<string> weather{"climate","weather","atmosphere","humidity", "forecast"};
static vector<string> fact{"funny","something", "surprise","interesting", "truth" "tell"};
static vector<string> timing{"morning","afternoon", "evening","today", "tomorrow", "yesterday"};
static vector<string> expectedTime{"next", "last", "on", "at"};


class CIntentType
{
private:
    string m_vtype;
    string m_vcity;
    string m_vtime;


    
public:
    CIntentType(const string & strSentence);
    ~CIntentType();
    string getType();
    string getCity();
    string getTime();
    static vector<string> IntentOutput(const vector<string> & words);
    static vector<string> StringToWords(const string & strInput);
    

};

CIntentType::~CIntentType()
{
    
}

string CIntentType::getType()
{
    return this->m_vtype;
}
string CIntentType::getCity()
{
    return this->m_vcity;
}

string CIntentType::getTime()
{
    return this->m_vtime;
}

vector<string> CIntentType::StringToWords(const string & strInput)
{
    istringstream ss(strInput);   
    string individual_word;
    vector<string> words;

    while( ss >> individual_word)
    {
        words.push_back(individual_word);
    }

    return words;
}

CIntentType::CIntentType(const string & strSentence)    
{
    vector<string> vwords = StringToWords(strSentence);
    vector<string> vparams = IntentOutput(vwords);
    this->m_vtype = vparams[0];
    this->m_vcity = vparams[1];
    this->m_vtime = vparams[2];
}


//checking each word by using clue and fetch the Intent according to that

vector<string> CIntentType::IntentOutput(const vector<string> & m_vwords)
{
    vector<string> m_vparams;
    string strcity;
    string strtype;
    //init flags for finding words
    bool bexpect_city = false;
    bool bexpect_time = false;
    bool bhasWeather = false;
    bool bhasFactClue = false;
    string strtimePhrase = "";

    for (auto word : m_vwords)
    {
        for (int i = 0; i < word.size(); i++) 
        {
            //for case-insensitive comparison and convert UpperCase to lower
            if (word[i] >= 'A' && word[i] <= 'Z')
                word[i]= tolower(word[i]);
            
            //Remove the special characters
            else if (word[i] < 'a' || word[i] > 'z')
            {
                word.erase(i, 1);
                i--;
            }
        }

        if(bexpect_city)
        {
            bexpect_city = false;
            strcity = word;
        }
        else if(bexpect_time)
        {
            bexpect_time = false;
            strtimePhrase += " "+ word;
        }

        if (find(fact.begin(), fact.end(), word) != fact.end() )
            bhasFactClue = true;
        
        else if (find(weather.begin(), weather.end(), word) != weather.end() )
            bhasWeather= true;
        
        else if(word.compare("in") == 0)
            bexpect_city = true;
        
        else if (find(expectedTime.begin(), expectedTime.end(), word) != expectedTime.end() )
        {
            bexpect_time = true;
            strtimePhrase = word;
        }
        else if (find(timing.begin(), timing.end(), word) != timing.end() )
        {
            strtimePhrase = word;
        }    
    }
  

    //Conditions for get Intent according to clues 

    strtype = bhasWeather ? strcity.empty() ? "Get Weather" : "Get Weather City": bhasFactClue? "Get Fact": "Intent Not Found";




    //params: 0-type 1-city 2-timePhrase
    m_vparams.push_back(strtype);
    m_vparams.push_back(strcity);
    m_vparams.push_back(strtimePhrase);
    return m_vparams;
}


int main()
{
    system("cls");

    cout<<"\t<###################################  Embedded Intent Recognizer ########################################"<<endl<<endl;

    string strinput;
    string username;
    string getIntent;

    cout<<"******************************************************"<<endl;
    
    cout << "Enter your question ==>" << endl;
    string phrase = "Enter your question";
    string command = "espeak \"" + phrase + "\"";
    const char *charCommand = command.c_str();
    system(charCommand);
    
    STARTUPINFO startInfo = {0};
    PROCESS_INFORMATION processInfo = {0};

    getline(cin,strinput);

    CIntentType intent(strinput);   

    cout << intent.getType() << endl; 
        
}
