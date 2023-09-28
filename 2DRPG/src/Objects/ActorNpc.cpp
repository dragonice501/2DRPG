#include "ActorNpc.h"

#include "../Utils/Utils.h"

const std::vector<std::string>& ActorNpc::GetCurrentDialogue() const
{
    switch (mCurrentDialogueMode)
    {
        case ED_GREETING:
        {
            return mDialogueMap.at(mCurrentDialogueKey)[mCurrentDialogueIndex];
        }
        case ED_INFORMATION:
        {
            return mInformationMap.at(mCurrentInformationKey)[mCurrentDialogueIndex];
        }
        case ED_ANSWER:
        {
            return mAnswersMap.at(mCurrentAnswerKey)[mCurrentDialogueIndex];
        }
    }
}

const EJournalType ActorNpc::GetKeywordType()
{
    std::string string = mInformationMap.begin()->first;

    for (auto it = mKeywordType.begin(); it != mKeywordType.end(); it++)
    {
        if (string == it->first)
        {
            return it->second;
        }
    }

    return EJ_NONE;
}

bool ActorNpc::CycleThroughDialogue()
{
    mCurrentDialogueIndex++;
    switch (mCurrentDialogueMode)
    {
        case ED_GREETING:
        {
            if (mCurrentDialogueIndex >= mDialogueMap[mCurrentDialogueKey].size())
            {
                mCurrentDialogueIndex = 0;
                return false;
            }
            break;
        }
        case ED_INFORMATION:
        {
            if (mCurrentDialogueIndex >= mInformationMap[mCurrentInformationKey].size())
            {
                mCurrentDialogueIndex = 0;
                return false;
            }
            break;
        }
        case ED_ANSWER:
        {
            if (mCurrentDialogueIndex >= mAnswersMap[mCurrentAnswerKey].size())
            {
                mCurrentDialogueIndex = 0;
                return false;
            }
            break;
        }
        case ED_NONE:
        {
            break;
        }
    }

    return true;
}

void ActorNpc::LoadDialogue(const std::string filePathName)
{
    EDialogueType dialogueType = ED_NONE;
    std::string diaglogue;
    std::vector<std::string> dialogueBlock;
    std::vector<std::vector<std::string>> dialogueVec;

    std::string dialogueLine;
    std::string keyWord;
    std::string keywordJournalType;

    std::string  fileName = "./assets/" + filePathName + ".txt";
    std::ifstream file(fileName);
    std::string text;
    while (file >> text)
    {
        if (text == "//")
        {
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (text == "Greeting")
        {
            dialogueType = ED_GREETING;
            continue;
        }
        else if (text == "Information")
        {
            dialogueType = ED_INFORMATION;
            file >> keywordJournalType >> keyWord;
            continue;
        }
        else if (text == "Answer")
        {
            dialogueType = ED_ANSWER;
            file >> keyWord;
            continue;
        }
        else if (text == "Break")
        {
            dialogueVec.push_back(dialogueBlock);

            dialogueLine.clear();
            dialogueBlock.clear();
        }
        else if (text == "End")
        {
            dialogueVec.push_back(dialogueBlock);

            switch (dialogueType)
            {
                case ED_GREETING:
                {
                    mDialogueMap.emplace("Greeting", dialogueVec);
                    break;
                }
                case ED_INFORMATION:
                {
                    mInformationMap.emplace(keyWord, dialogueVec);
                   
                    if (keywordJournalType == "Person") mKeywordType.emplace(keyWord, EJ_PERSON);
                    else if (keywordJournalType == "Place") mKeywordType.emplace(keyWord, EJ_PLACE);
                    else if (keywordJournalType == "Mystery") mKeywordType.emplace(keyWord, EJ_MYSTERY);
                    else if (keywordJournalType == "Bestiary") mKeywordType.emplace(keyWord, EJ_BESTIARY);
                    break;
                }
                case ED_ANSWER:
                {
                    mAnswersMap.emplace(keyWord, dialogueVec);
                    break;
                }
                case ED_NONE:
                {
                    break;
                }
            }

            dialogueBlock.clear();
            dialogueVec.clear();

            dialogueType = ED_NONE;
        }
        else
        {
            std::string string;
            std::getline(file, string);

            dialogueLine = text + string;

            dialogueBlock.push_back(dialogueLine);
        }
    }

    if (mDialogueMap.size() > 0)
    {
        mCurrentDialogueKey = mDialogueMap.begin()->first;
    }

    if (mInformationMap.size() > 0)
    {
        mCurrentInformationKey = mInformationMap.begin()->first;
    }

    if (mAnswersMap.size() > 0)
    {
        mCurrentAnswerKey = mAnswersMap.begin()->first;
    }
}

bool ActorNpc::HasNewInformation()
{
    if (mInformationMap.size() == 0) return false;

    std::vector<std::string> vec = PlayerManager::GetPeopleKeywords();
    for (int i = 0; i < vec.size(); i++)
    {
        for (auto it = mInformationMap.begin(); it != mInformationMap.end(); it++)
        {
            if (it->first == vec[i])
            {
                return false;
            }
        }
    }

    vec = PlayerManager::GetPlacesKeywords();
    for (int i = 0; i < vec.size(); i++)
    {
        for (auto it = mInformationMap.begin(); it != mInformationMap.end(); it++)
        {
            if (it->first == vec[i])
            {
                return false;
            }
        }
    }

    vec = PlayerManager::GetMysteryKeywords();
    for (int i = 0; i < vec.size(); i++)
    {
        for (auto it = mInformationMap.begin(); it != mInformationMap.end(); it++)
        {
            if (it->first == vec[i])
            {
                return false;
            }
        }
    }

    vec = PlayerManager::GetBestiaryKeywords();
    for (int i = 0; i < vec.size(); i++)
    {
        for (auto it = mInformationMap.begin(); it != mInformationMap.end(); it++)
        {
            if (it->first == vec[i])
            {
                return false;
            }
        }
    }

    return true;
}

bool ActorNpc::HasAnswerToKeyword(const std::string& keyword)
{
    if (mAnswersMap.size() == 0) return false;

    for (auto it = mAnswersMap.begin(); it != mAnswersMap.end(); it++)
    {
        if (keyword == it->first)
        {
            return true;
        }
    }

    return false;
}