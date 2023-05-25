// 헤더 선언
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
using namespace std;
#include <iostream>

// 상수 선언
#define MAX_STRING 32
#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"

FILE* in_fp, * out_fp;

class MemberInfo
{
private:
    char id[MAX_STRING];
    char pw[MAX_STRING];
public:
    MemberInfo()
    {
        strcpy(this->id, "");
        strcpy(this->pw, "");
    };
    MemberInfo(char _id[], char _pw[])
    {
        strcpy(this->id, _id);
        strcpy(this->pw , _pw);
    }
    char* getId() { return this->id; }
    char* getPw() { return this->pw; }
};

class CompanyMemberInfo : public MemberInfo
{
private:
    char companyName[MAX_STRING];
    char companyNum[MAX_STRING];
public:
    CompanyMemberInfo()
    {
        strcpy(this->companyName, "");
        strcpy(this->companyNum, "");
    };
    CompanyMemberInfo(char _comName[], char _comNum[], char _id[], char _pw[])
        :MemberInfo(_id, _pw)
    {
        strcpy(this->companyName, _comName);
        strcpy(this->companyNum, _comNum);
    
    }
    char* getName() { return this->companyName; }
    char* getNum() { return this->companyNum; }
};

class GeneralMemberInfo : public MemberInfo
{
private:
    char name[MAX_STRING];
    char resisdentNum[MAX_STRING];
public:
    GeneralMemberInfo()
    {
        strcpy(this->name, "");
        strcpy(this->resisdentNum, "");
    };
    GeneralMemberInfo(char _name[], char _reNum[], char _id[], char _pw[])
        :MemberInfo(_id, _pw)
    {
        strcpy(this->name, _name);
        strcpy(this->resisdentNum, _reNum);
    }
    char* getName() { return this->name; }
    char* getNum() { return this->resisdentNum; }
};

class MemberManagement
{
private:
    CompanyMemberInfo* comMemberArr;
    GeneralMemberInfo* genMemberArr;

    int comMemberNum;
    int genMemberNum;

    char currId[MAX_STRING];
    char currPw[MAX_STRING];
public:
    MemberManagement()
    {
        this->comMemberArr = new CompanyMemberInfo[20]{};
        this->genMemberArr = new GeneralMemberInfo[20]{};
        this->comMemberNum = 0;
        this->genMemberNum = 0;
        strcpy(this->currId, "");
        strcpy(this->currPw, "");
    }
    void createNewCompanyMember(char _comName[], char _comNum[], char _id[], char _pw[])
    {
        CompanyMemberInfo comMemInfo = CompanyMemberInfo(_comName, _comNum, _id, _pw);
        this->comMemberArr[comMemberNum] = comMemInfo;
        this->comMemberNum += 1;
        cout << comMemberNum;
    }
    void createNewGeneralMember(char _name[], char _residNum[], char _id[], char _pw[])
    {
        GeneralMemberInfo genMemInfo = GeneralMemberInfo(_name, _residNum, _id, _pw);
        this->genMemberArr[genMemberNum] = genMemInfo;
        this->genMemberNum += 1;
    }
    void memberLogin(char id[], char pw[])
    {
        strcpy(this->currId, id);
        strcpy(this->currPw, pw);
    }
    int classifyMember()
    {
        for (int i = 0; i < comMemberNum; i++)
        {
            if (find(this->currId, this->comMemberArr[i].getId()) == 0)
            {
                return 1;
            }
        }
        for (int j = 0; j < genMemberNum; j++)
        {
            if (find(this->currId, this->genMemberArr[j].getId()) == 0)
            {
                return 2;
            }
        }
    }


    char* memberLogout()
    {
        strcpy(this->currId, "");
        strcpy(this->currPw, "");
        return this->currId;
    }
    char* memberWithdraw()
    {
        return this->currId;
    }

    bool find(const char* str_ido, const char* str_idt) 
    {
        return strcmp(str_ido, str_idt);
    };

    char* findCurrMemberName()
    {
        for (int i = 0; i < comMemberNum; i++)
        {
            if (find(this->currId, this->comMemberArr[i].getId()) == 0)
            {
                return this->comMemberArr[i].getName();
            }
        }
    }

    char* findCurrMemberNum()
    {
        for (int i = 0; i < comMemberNum; i++)
        {
            if (find(this->currId, this->comMemberArr[i].getId()) == 0)
            {
                return this->comMemberArr[i].getNum();
            }
        }
    }
    char* getCurrId()
    {
        return this->currId;
    }
};

MemberManagement memberMng;

class Join
{
private:
    char type[MAX_STRING];
public:
    Join(){ strcpy(type, ""); }
   
    void requestJoin(char m[], char _one[], char _two[], char _three[], char _four[])
    {
        strcpy(this->type, m);

        if (strcmp(type, "1")==0)
        {
            memberMng.createNewCompanyMember(_one, _two, _three, _four);
        }
        else if(strcmp(type, "2")==0)
        {
            memberMng.createNewGeneralMember(_one, _two, _three, _four);
        }
    }
};

class JoinUI
{
public:
    void clickJoin()
    {
        char memberType[MAX_STRING];
        fscanf(in_fp, "%s \n", &memberType);

        Join join;
        fprintf(out_fp, "1.1. 회원가입\n");
        fprintf(out_fp, "> %s ", &memberType);

        char one[MAX_STRING], two[MAX_STRING], three[MAX_STRING], four[MAX_STRING];
        fscanf(in_fp, "%s %s %s %s\n", &one, &two, &three, &four);
        join.requestJoin(memberType, one, two, three, four);
        fprintf(out_fp, "%s %s %s %s\n", one, two, three, four);
    }
};

class Login
{
public:
    void requestLogin(char _id[MAX_STRING], char _pw[MAX_STRING])
    {
        memberMng.memberLogin(_id, _pw);
    }
};

class LoginUI
{
public:
    void enterIdPw()
    {
        char id[MAX_STRING], pw[MAX_STRING];
        fscanf(in_fp, "%s %s ", id, pw);
        Login login;
        login.requestLogin(id, pw);
        fprintf(out_fp, "2.1. 로그인\n");
        fprintf(out_fp, "> %s %s\n", id, pw);
    }
};

class Logout
{
public:
    char* requestLogout()
    {
        return memberMng.memberLogout();
    }
};

class LogoutUI
{
public:
    void clickLogout()
    {
        Logout logout;
        char id[MAX_STRING]="";
        strcpy(logout.requestLogout(), id);
        fprintf(out_fp, "2.1. 로그아웃\n");
        fprintf(out_fp, "> %s\n ", id);
    }
};

class Withdraw
{
public:
    char* requestWithdrawl()
    {
        return memberMng.memberWithdraw();
    }
};

class WithdrawUI
{
public:
    void clickWithdrawal()
    {
        Withdraw withdraw;
        fprintf(out_fp, "1.2. 탈퇴\n");
        fprintf(out_fp, "> %s\n ", withdraw.requestWithdrawl());
    }
};

//////////////////////////////////////////////////////////////////////////////

class Employment
{
private:
    char companyName[MAX_STRING];
    char companyNum[MAX_STRING];
    char businessTask[MAX_STRING];
    char recruitingNum[MAX_STRING];
    char deadline[MAX_STRING];
public:
    Employment()
    {
        strcpy(this->companyName, "");
        strcpy(this->companyNum, "");
        strcpy(this->businessTask, "");
        strcpy(this->recruitingNum, "");
        strcpy(this->deadline, "");
    };
    Employment(char cName[], char cNum[], char bTask[], char rNum[], char dline[])
    {
        strcpy(companyName, cName);
        strcpy(companyNum, cNum);
        strcpy(businessTask, bTask);
        strcpy(recruitingNum, rNum);
        strcpy(deadline, dline);
    }
    char* getCompanyName() { return this->companyName; }
    char* getCompanyNum() { return this->companyNum; }
    char* getBusinessTask() { return this->businessTask; }
    char* getrecruitingNum() { return this->recruitingNum; }
    char* getdeadline() { return this->deadline; }

};

class EmploymentManager
{
private:
    Employment* employmentArr;
    int employmentArrNum;
    int arrNumForInstance;
public:
    EmploymentManager()
    {
        employmentArr = new Employment[20]{};
        employmentArrNum = 0;
        arrNumForInstance = 0;
    }

    void createNewEmployment(char cName[], char cNum[], char bTask[], char rNum[], char dline[])
    {
        Employment emp = Employment(cName, cNum, bTask, rNum, dline);
        employmentArr[employmentArrNum] = emp;
        employmentArrNum += 1;
    }

    Employment* getCertainMemberEmployments(char comName[])
    {
        Employment *thisMemEmps = new Employment[20];
        arrNumForInstance = 0;
        for (int i = 0; i < employmentArrNum; i++)
        {
            if (strcmp(employmentArr[i].getCompanyName(),comName) == 0)
            {
                thisMemEmps[arrNumForInstance] = employmentArr[i];
                arrNumForInstance += 1;
            }
        }
        return thisMemEmps;
    }

    Employment getEmploymentByNum(char comNum[])
    {
        Employment thisMemEmp;
        for (int i = 0; i < employmentArrNum; i++)
        {
            if (strcmp(employmentArr[i].getCompanyNum(), comNum) == 0)
            {
                thisMemEmp = employmentArr[i];
            }
        }
        return thisMemEmp;
    }

    int arrNum()
    {
        return arrNumForInstance;
    }
 
};

EmploymentManager employmentMng;

class RegisterEmployment
{
public:
    void registerNewEmployment(char businessTask[], char recruitingNum[], char deadline[])
    {
        employmentMng.createNewEmployment(memberMng.findCurrMemberName(), memberMng.findCurrMemberNum(), businessTask, recruitingNum, deadline);
    }
};

class RegisterEmploymentUI
{
public:
    void clickRegisterEmployment()
    {
        char businessTask[MAX_STRING], recruitingNum[MAX_STRING], deadline[MAX_STRING];
        fscanf(in_fp, "%s %s %s", businessTask, recruitingNum, deadline);
        
        RegisterEmployment registerEmployment;
        registerEmployment.registerNewEmployment(businessTask, recruitingNum, deadline);
        
        fprintf(out_fp, "3.1. 채용 정보 등록\n");
        fprintf(out_fp, "> %s %s % s\n", businessTask, recruitingNum, deadline);
    }
};

class ShowEmplList
{
public:
    Employment* showEmployment()
    {
        char currMem[20];
        strcpy(currMem,memberMng.findCurrMemberName());

        Employment* empList;
        empList = employmentMng.getCertainMemberEmployments(currMem);
        return empList;
    }

};

class ShowEmplListUI
{
public:
    void selectEmployment()
    {
        ShowEmplList showEmpList;
        Employment* thisMemEmps;
        
        thisMemEmps = showEmpList.showEmployment();

        fprintf(out_fp, "3.2. 등록된 채용 정보 조회\n");
        for (int i = 0; i < employmentMng.arrNum(); i++)
        {
            if (thisMemEmps[i].getBusinessTask() != NULL)
            {
                fprintf(out_fp, "> %s %s %s\n" , thisMemEmps[i].getBusinessTask(), thisMemEmps[i].getrecruitingNum(), thisMemEmps[i].getdeadline());
            }
            
        }
    }
};

///////////////////////////////////////////////////////////////////////

class Application
{
private:
    char applicantId[MAX_STRING];
    char companyName[MAX_STRING];
    char companyNum[MAX_STRING];
    char businessTask[MAX_STRING];
    char recruitingNum[MAX_STRING];
    char deadline[MAX_STRING];
public:
    Application()
    {
        strcpy(this->applicantId, "");
        strcpy(this->companyName, "");
        strcpy(this->companyNum, "");
        strcpy(this->businessTask, "");
        strcpy(this->recruitingNum, "");
        strcpy(this->deadline, "");
    }
    Application(char id[], char cName[], char cNum[], char bTask[], char rNum[], char dline[])
    {
        strcpy(applicantId, id);
        strcpy(companyName, cName);
        strcpy(companyNum, cNum);
        strcpy(businessTask, bTask);
        strcpy(recruitingNum, rNum);
        strcpy(deadline, dline);
    }
    char* getId() { return this->applicantId; }
    char* getCompanyName() { return this->companyName; }
    char* getCompanyNum() { return this->companyNum; }
    char* getBusinessTask() { return this->businessTask; }
    char* getrecruitingNum() { return this->recruitingNum; }
    char* getdeadline() { return this->deadline; }
    
};

class ApplicationManager
{
private:
    Application* applicationArr;
    int applicationArrNum;
    int arrNumForInstance;
public:
    ApplicationManager()
    {
        applicationArr = new Application[20]{};
        applicationArrNum = 0;
        arrNumForInstance = 0;
    }

    void createNewApplication(char id[], char cName[], char cNum[], char bTask[], char rNum[], char dline[])
    {
        Application app = Application(id, cName, cNum, bTask, rNum, dline);
        applicationArr[applicationArrNum] = app;
        applicationArrNum += 1;
    }
    Application* getCertainMemberApplications(char genId[])
    {
        Application* thisMemApps = new Application[20];
        arrNumForInstance = 0;
        for (int i = 0; i < applicationArrNum; i++)
        {
            if (strcmp(applicationArr[i].getId(), genId) == 0)
            {
                thisMemApps[arrNumForInstance] = applicationArr[i];
                arrNumForInstance += 1;
            }
        }
        return thisMemApps;
    }
    Application getApplicationByNum(char cNum[])
    {
        Application thisMemApp;
        cout << applicationArrNum;
        for (int i = 0; i < applicationArrNum; i++)
        {
            cout << applicationArr[i].getCompanyNum();
            if (strcmp(applicationArr[i].getCompanyNum(), cNum) == 0)
            {
                thisMemApp = applicationArr[i];
            }
        }
        return thisMemApp;
    }
    void destroyApplication(Application app)
    {
        for (int i = 0; i < applicationArrNum; i++)
        {
            if (&applicationArr[i] == &app)
            {
                delete &applicationArr[i];
            }
        }
    }

    char* AllTasks(Employment* _thisMemEmp)
    {
        char task[20][20];
        int taskNum = 0;
        for (int i = 0; i < employmentMng.arrNum(); i++)
        {
            strcpy(task[i], _thisMemEmp->getBusinessTask());
            taskNum += 1;
        }
        return *task;
    }
    int* StatisticsForCompany(char *tasks)
    {
        char thisMem[20];
        strcpy(thisMem, memberMng.getCurrId());
        Employment* thisMemEmp = employmentMng.getCertainMemberEmployments(thisMem);
       
        char* task = tasks;
        int applyNum[20];

        for (int i = 0; i < 20; i++)
        {
            int num = 0;
            for (int j = 0; j < applicationArrNum; j++)
            {
                if (strcmp(applicationArr[j].getBusinessTask(), &task[i]) == 0)
                {
                    num += 1;
                }
            }
            applyNum[i] = num;
        }

        return applyNum;
    }
    void StatisticsForGeneral()
    {

    }


    int arrNum()
    {
        return arrNumForInstance;
    }
};

ApplicationManager applicationMng;

class SearchCompany
{
public:
    Employment* getEmploymentByCompany(char* Name)
    {
        return employmentMng.getCertainMemberEmployments(Name);
       
    }
};

class SearchCompanyUI
{
public:
    void searchByCompany()
    {
        char cName[MAX_STRING];
        fscanf(in_fp, "%s \n", cName);

        SearchCompany searchCompany;
        Employment* searchedEmpsArr;

        searchedEmpsArr = searchCompany.getEmploymentByCompany(cName);

        fprintf(out_fp, "4.1. 채용 정보 검색\n");
        for (int i = 0; i < employmentMng.arrNum(); i++)
        {
            if (searchedEmpsArr[i].getBusinessTask() != NULL)
            {
                fprintf(out_fp, "> %s %s % s %s %s\n", searchedEmpsArr[i].getCompanyName(), searchedEmpsArr[i].getCompanyNum(), searchedEmpsArr[i].getBusinessTask(), searchedEmpsArr[i].getrecruitingNum(), searchedEmpsArr[i].getdeadline());
            }
        }
    }
};

class Apply
{
public:
    Employment applyEmployment(char num[])
    {
        Employment empToApply = employmentMng.getEmploymentByNum(num);
        applicationMng.createNewApplication(memberMng.getCurrId(), empToApply.getCompanyName(), empToApply.getCompanyNum(), empToApply.getBusinessTask(), empToApply.getrecruitingNum(), empToApply.getdeadline());
        return empToApply;
    }
};

class ApplyUI
{
public:
    void selectEmployment()
    {
        char cNum[MAX_STRING];
        fscanf(in_fp, "%s \n", cNum);

        Apply apply;
        Employment emp = apply.applyEmployment(cNum);
        fprintf(out_fp, "4.2. 채용 지원\n");
        fprintf(out_fp, "> %s %s % s\n", emp.getCompanyName(), emp.getCompanyNum(), emp.getBusinessTask());
    }
};

class ShowApply 
{
public:
    Application* showApplicationDetails()
    {
        char currMem[20];
        strcpy(currMem ,memberMng.getCurrId());
        Application* appList;
        appList = applicationMng.getCertainMemberApplications(currMem);
        return appList;

    }
};

class ShowApplyUI
{
public:
    void selectApplication()
    {
        ShowApply showApp;
        Application* thisMemApps;

        thisMemApps = showApp.showApplicationDetails();

        fprintf(out_fp, "4.3. 지원 정보 조회\n");
        for (int i = 0; i < applicationMng.arrNum(); i++)
        {
            if (thisMemApps[i].getId() != NULL)
            {
                fprintf(out_fp, "> %s %s %s %s %s\n", thisMemApps[i].getCompanyName(), thisMemApps[i].getCompanyNum(), thisMemApps[i].getBusinessTask(), thisMemApps[i].getrecruitingNum(), thisMemApps[i].getdeadline());
            }

        }
    }
};

class CancelApply
{
public:
    Application deleteApplication(char num[])
    {
        Application app = applicationMng.getApplicationByNum(num);
        applicationMng.destroyApplication(app);
        return app;
    }
};

class CancelApplyUI
{
public:
    void cancelApplication()
    {
        char cNum[MAX_STRING];
        fscanf(in_fp, "%s \n", cNum);

        CancelApply cancelApply;
        Application app = cancelApply.deleteApplication(cNum);
        fprintf(out_fp, "4.4. 지원 취소\n");
        fprintf(out_fp, "> %s %s % s\n", app.getCompanyName(), app.getCompanyNum(), app.getBusinessTask());
        
    }
};

/*
class PrintStatistics
{
public:
    void showStatisticsUI()
    {
        char currMem[20];
        strcpy(currMem, memberMng.getCurrId());
        if (memberMng.classifyMember() == 1)
        {
            char* tasks = applicationMng.AllTasks(employmentMng.getCertainMemberEmployments(currMem));
            int* nums = applicationMng.StatisticsForCompany(tasks);

            for (int i = 0; i < 20; i++)
            {
                if (tasks[i] != NULL)
                {
                    fprintf(out_fp, "> %s %s\n", tasks[i], nums[i]);
                }
            }
        }
        else if(memberMng.classifyMember() == 2)
        {

        }
    }
};

class PrintStatisticsUI
{
public:
    void getStatistics()
    {
        PrintStatistics printST;
        fprintf(out_fp, "5.1. 지원 정보 통계\n");
        printST.showStatisticsUI();
    };
};
*/

// 함수 선언
void doTask();
void program_exit();



int main()
{
    // 파일 입출력을 위한 초기화
    in_fp = fopen("input.txt", "r+");
    out_fp = fopen("output.txt", "w+");

    memberMng = MemberManagement();
    employmentMng = EmploymentManager();
    doTask();

    return 0;
}


void doTask()
{
    // 메뉴 파싱을 위한 level 구분을 위한 변수
    int menu_level_1 = 0, menu_level_2 = 0;
    int is_program_exit = 0;

    while (!is_program_exit)
    {
        // 입력파일에서 메뉴 숫자 2개를 읽기
        fscanf(in_fp, "%d %d ", &menu_level_1, &menu_level_2);


        // 메뉴 구분 및 해당 연산 수행
        switch (menu_level_1)
        {
            case 1:
            {
                switch (menu_level_2)
                {
                    case 1:
                    {
                        JoinUI joinui;
                        joinui.clickJoin();
                        break;
                    }
                    case 2:
                    {
                        WithdrawUI withdrawui;
                        withdrawui.clickWithdrawal();
                        break;
                    }
                }
                break;
            }
            case 2:
            {
                switch (menu_level_2)
                {
                case 1:
                {
                    LoginUI loginui;
                    loginui.enterIdPw();
                    break;
                }
                case 2:
                {

                }
                }
                break;
            }
            case 3:
            {
                switch (menu_level_2)
                {
                case 1:
                {
                    RegisterEmploymentUI registerempui;
                    registerempui.clickRegisterEmployment();
                    break;
                }
                case 2:
                {
                    ShowEmplListUI showEmp;
                    showEmp.selectEmployment();
                    //cout << memberMng.getCurrName();
                    break;
                }
                }
                break;
            }
            case 4:
            {
                switch (menu_level_2)
                {
                case 1:
                {
                    SearchCompanyUI searchcomui;
                    searchcomui.searchByCompany();
                    break;
                }
                case 2:
                {
                    ApplyUI applyui;
                    applyui.selectEmployment();
                    break;
                }
                case 3:
                {
                    ShowApplyUI showAppui;
                    showAppui.selectApplication();
                    break;
                }
                case 4:
                {
                    CancelApplyUI cancelAppui;
                    cancelAppui.cancelApplication();
                    break;
                }
                }
                break;
            }
            case 5:
            {
                switch (menu_level_2)
                {
                case 1:   
                {/*
                    PrintStatisticsUI printstui;
                    printstui.getStatistics();
                    break;
                    */
                }
                }
            }
            case 6:
            {
                switch (menu_level_2)
                {
                    case 1:   // "6.1. 종료“ 메뉴 부분
                    {
                        program_exit();
                        is_program_exit = 1;
                        break;
                    }
                }
            }
        }

    }
    return;
}

void program_exit()
{
    fprintf(out_fp, "6.1. 종료\n");

}