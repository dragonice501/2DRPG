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
            file >> keyWord;
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

bool ActorNpc::HasNewInformation(const std::vector<std::string> learnedWords)
{
    if (mInformationMap.size() == 0) return false;

    for (const std::string& word : learnedWords)
    {
        for (auto it = mInformationMap.begin(); it != mInformationMap.end(); it++)
        {
            if (word == it->first)
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
