/*
grandpa
.mom
..my brother
..me
...my daughter
...my son
..my sister
...my nephew
.my uncle
..uncle son
*/

class Tree{
private:
    struct TreeNode{
        TreeNode(const std::string& str = "") : val(str)
        {}
        
        ~TreeNode()
        {
            while(!pVec.empty())
            {
                TreeNode* pTemp = pVec.back();
                pVec.pop_back();
                delete pTemp;
            }
        }
        std::string val;
        std::vector<TreeNode*> pVec;
    };
    
public:
    void initTree()
    {
        std::istringstream input;
        input.str("grandpa\n.mom\n..my brother\n..me\n...my daughter\n...my son\n..my sister\n...my nephew\n.my uncle\n..uncle son\n");
        
        auto getPeriodCount = [](const std::string& str)->int
        {
            int count = 0;
            for(auto ch : str)
            {
                if(ch == '.')
                    ++count;
                else
                    break;
            }
            return count;
        };
        std::string str;
        int preCount = 0;
        std::vector<TreeNode*> parents;
        TreeNode* pInsert = nullptr;
        TreeNode* pCur = nullptr;
        
        while(std::getline(input, str))
        {
            int count = getPeriodCount(str);

            if(pTree == nullptr)
            {
                if(count != 0)
                    continue;
                pTree = new TreeNode(str);
                pInsert = pTree;
                pCur = pTree;
            }
            else
            {
                count = getPeriodCount(str);
                if(count > preCount + 1)
                    continue;
                else if(count == preCount + 1)
                {
                    parents.emplace_back(pCur);
                    pInsert = pCur;
                }
                else if(preCount > count)
                {
                    while(preCount != count)
                    {
                        parents.pop_back();
                        --preCount;
                    }
                    pInsert = parents.back();
                }
                
                pCur = new TreeNode(str);
                pInsert->pVec.emplace_back(pCur);
                preCount = count;
            }
        }
    }
    
    std::vector<TreeNode*> BFS(TreeNode* pRoot)
    {
        if(pRoot == nullptr) return {};
        std::deque<TreeNode*> pQue;
        pQue.emplace_back(pRoot);
        std::vector<TreeNode*> result;
        result.emplace_back(pRoot);
        
        while(!pQue.empty())
        {
            TreeNode* pTemp = pQue.front();
            pQue.pop_front();
            for(int i = 0, iEnd = pTemp->pVec.size(); i < iEnd; ++i)
            {
                result.emplace_back(pTemp->pVec[i]);
                pQue.emplace_back(pTemp->pVec[i]);
            }
        }
        return result;
    }
    
    std::vector<TreeNode*> DFS(TreeNode* pRoot)
    {
        if(pRoot == nullptr) return {};
        std::stack<std::pair<TreeNode*, int>> pSta;
        pSta.emplace(std::make_pair(pRoot, 0));
        std::vector<TreeNode*> result;
        result.emplace_back(pRoot);
        
        while(!pSta.empty())
        {
            auto& pTemp = pSta.top();
            if(pTemp.second == pTemp.first->pVec.size())
                pSta.pop();
           
            else
            {
                result.emplace_back(pTemp.first->pVec[pTemp.second]);
                pSta.emplace(std::make_pair(pTemp.first->pVec[pTemp.second], 0));
                ++pTemp.second;
            }
        }
        return result;
    }

    std::vector<TreeNode*> DFS_sorted(TreeNode* pRoot)
    {
        if(pRoot == nullptr) return {};
        std::stack<TreeNode*> pSta;
        pSta.emplace(pRoot);
        std::vector<TreeNode*> result;
        
        while(!pSta.empty())
        {
            auto pTemp = pSta.top();
            pSta.pop();
            result.emplace_back(pTemp);
            
            if(!pTemp->pVec.empty())
            {
                std::sort(pTemp->pVec.begin(), pTemp->pVec.end(),
                          [](TreeNode* a, TreeNode* b){
                              return a->val < b->val;
                          });
                for (auto it = pTemp->pVec.crbegin(); it != pTemp->pVec.crend(); ++it)
                {
                    pSta.push(*it);
                }            }
        }
        return result;
    }

    
private:
    TreeNode* pTree = nullptr;
};
