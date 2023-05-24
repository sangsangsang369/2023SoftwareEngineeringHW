#include <iostream>
#include <string>

using namespace std;

// 최대 지원 정보 개수
const int MAX_APPLICATIONS = 100;

// 회원 구조체
struct Member {
    string id;
    string pw;
    bool isCompanyMember;
};

// 지원 정보 구조체
struct Application {
    string companyName;
    string businessNumber;
    string buisnessTask;
    int recruitingNum;
    string deadline;
    string name;
};

// 지원 정보 배열
Application application[MAX_APPLICATIONS];
int numApplications = 0;

// 회원 배열
Member members[MAX_APPLICATIONS];
int numMembers = 0;

// 로그인된 회원
Member* loggedInMember = nullptr;

// 회원 가입 함수
void signUp() {
    if (numMembers >= MAX_APPLICATIONS) {
        cout << "더 이상 회원을 추가할 수 없습니다." << endl;
        return;
    }

    Member newMember;

    cout << "사용자 이름: ";
    cin >> newMember.id;

    cout << "비밀번호: ";
    cin >> newMember.pw;

    cout << "회원 유형(1: 회사 회원, 0: 일반 사용자): ";
    cin >> newMember.isCompanyMember;

    members[numMembers] = newMember;
    numMembers++;

    cout << "회원 가입이 완료되었습니다." << endl;
}

// 로그인 함수
void login() {
    if (loggedInMember != nullptr) {
        cout << "이미 로그인되어 있습니다." << endl;
        return;
    }

    string id, pw;
    cout << "사용자 이름: ";
    cin >> id;

    cout << "비밀번호: ";
    cin >> pw;

    for (int i = 0; i < numMembers; i++) {
        if (members[i].id == id && members[i].pw == pw) {
            loggedInMember = &members[i];
            cout << "로그인되었습니다." << endl;
            return;
        }
    }

    cout << "일치하는 회원 정보를 찾을 수 없습니다." << endl;
}

// 로그아웃 함수
void logout() {
    if (loggedInMember == nullptr) {
        cout << "로그인되어 있지 않습니다." << endl;
        return;
    }

    loggedInMember = nullptr;
    cout << "로그아웃되었습니다." << endl;
}

void sortApplicationsByCompanyName() {
    for (int i = 0; i < numApplications - 1; i++) {
        for (int j = 0; j < numApplications - i - 1; j++) {
            if (application[j].companyName > application[j + 1].companyName) {
                // Swap applications[j] and applications[j + 1]
                Application temp = application[j];
                application[j] = application[j + 1];
                application[j + 1] = temp;
            }
        }
    }
}

// 채용 정보를 등록하는 함수 (회사 회원)
void registerJobOpening() {
    if (loggedInMember == nullptr || !loggedInMember->isCompanyMember) {
        cout << "회사 회원으로 로그인해야 합니다." << endl;
        return;
    }

    if (numApplications >= MAX_APPLICATIONS) {
        cout << "더 이상 채용 정보를 등록할 수 없습니다." << endl;
        return;
    }

    Application newApplication;

    cout << "회사 이름: ";
    cin >> newApplication.companyName;

    cout << "사업자 번호: ";
    cin >> newApplication.businessNumber;

    cout << "업무: ";
    cin >> newApplication.buisnessTask;

    cout << "인원 수: ";
    cin >> newApplication.recruitingNum;

    cout << "신청 마감일: ";
    cin >> newApplication.deadline;

    newApplication.name = loggedInMember->id;

    application[numApplications] = newApplication;
    numApplications++;

    cout << "채용 정보가 등록되었습니다." << endl;
}

// 채용 정보를 검색하는 함수 (일반 사용자)
void searchJobOpening() {
    if (loggedInMember == nullptr) {
        cout << "로그인이 필요합니다." << endl;
        return;
    }

    string companyName;
    cout << "검색할 회사 이름: ";
    cin >> companyName;

    bool found = false;

    for (int i = 0; i < numApplications; i++) {
        if (application[i].companyName == companyName) {
            cout<<application[i].companyName<<" "<<application[i].buisnessTask<<" "<<application[i].recruitingNum<<" "<<application[i].deadline<<endl;

                found = true;
        }
    }

    if (!found) {
        cout << "검색한 회사의 채용 정보를 찾을 수 없습니다." << endl;
    }
}

// 지원 내역을 조회하는 함수 (일반 사용자)
void showApplicationDetails() {
    if (loggedInMember == nullptr) {
        cout << "로그인이 필요합니다." << endl;
        return;
    }

    cout << "지원 내역" << endl;
    sortApplicationsByCompanyName();
    
    // 해당 회원이 지원한 채용 정보를 조회하여 출력
    for (int i = 0; i < numApplications; i++) {
        if (application[i].name == loggedInMember->id) {
            cout<<application[i].companyName<<" "<<application[i].buisnessTask<<" "<<application[i].recruitingNum<<" "<<application[i].deadline<<endl;
        }
    }
}

// 지원을 취소하는 함수
void cancelApplication() {
    if (loggedInMember == nullptr) { // 로그인되어 있지 않은 경우
        cout << "로그인이 필요합니다." << endl;
        return;
    }
    int cancelApplicationIndex = -1; // 취소할 지원 정보의 인덱스
    string companyName;
    cout << "취소할 회사 이름: ";
    cin >> companyName;

    // 지원 정보 배열을 순회하면서 취소할 회사 이름과 회원의 지원 정보를 확인
    for (int i = 0; i < numApplications; i++) {
        if (application[i].companyName == companyName && application[i].name == loggedInMember->id) {
            cancelApplicationIndex = i; // 취소할 지원 정보의 인덱스를 저장
            break; // 해당 지원 정보를 찾았으므로 반복문 종료
        }
    }

    if (cancelApplicationIndex != -1) { // 취소할 지원 정보를 찾은 경우
        // 취소할 지원 정보를 삭제하고 배열을 재정렬
        for (int i = cancelApplicationIndex; i < numApplications - 1; i++) {
            application[i] = application[i + 1];
        }
        numApplications--; // 지원 정보 개수를 감소

        cout << "지원이 취소되었습니다." << endl;
    } else { // 취소할 지원 정보를 찾지 못한 경우
        cout << "해당 회사의 지원 정보를 찾을 수 없습니다." << endl;
    }

    if (numApplications == 0) { // 더 이상 취소할 지원 내역이 없는 경우
        cout << "더 이상 취소할 지원 내역이 없습니다." << endl;
    }
}

// 채용 정보 선택 및 지원하는 함수
void selectApplication() {
    if (loggedInMember == nullptr) { // 로그인되어 있지 않은 경우
        cout << "로그인이 필요합니다." << endl;
        return;
    }

    string companyName;
    cout << "지원할 회사 이름: ";
    cin >> companyName;

    int applicationIndex = -1; // 선택한 채용 정보의 인덱스를 저장하는 변수

    // 지원 정보 배열을 순회하면서 선택한 회사 이름과 일치하는 채용 정보를 찾음
    for (int i = 0; i < numApplications; i++) {
        if (application[i].companyName == companyName) {
            applicationIndex = i; // 선택한 채용 정보의 인덱스를 저장
            break; // 해당 채용 정보를 찾았으므로 반복문 종료
        }
    }

    if (applicationIndex != -1) { // 선택한 채용 정보를 찾은 경우
        Application selectedApplication = application[applicationIndex];

        cout << "===== 채용 정보 =====" << endl;
        cout << "회사 이름: " << selectedApplication.companyName << endl;
        cout << "사업자 번호: " << selectedApplication.businessNumber << endl;
        cout << "업무: " << selectedApplication.buisnessTask << endl;
        cout << "인원 수: " << selectedApplication.recruitingNum << endl;
        cout << "신청 마감일: " << selectedApplication.deadline << endl;
        cout << "---------------------" << endl;

        string choice;
        cout << "지원하시겠습니까? (Y/N): ";
        cin >> choice;

        if (choice == "Y" || choice == "y") { // 지원하는 경우
            selectedApplication.name = loggedInMember->id; // 현재 로그인한 회원의 ID로 지원 정보 업데이트
            application[applicationIndex] = selectedApplication;

            cout << "지원이 완료되었습니다." << endl;
        } else {
            cout << "지원이 취소되었습니다." << endl;
        }
    } else { // 선택한 채용 정보를 찾지 못한 경우
        cout << "해당 회사의 채용 정보를 찾을 수 없습니다." << endl;
    }
}


int main() {
    int choice;

    while (true) {
        cout << "====== 메뉴 ======" << endl;
        cout << "1. 회원 가입" << endl;
        cout << "2. 로그인" << endl;
        cout << "3. 로그아웃" << endl;
        cout << "4. 채용 정보 등록" << endl;
        cout << "5. 채용 정보 검색" << endl;
        cout << "6. 지원 내역 조회" << endl;
        cout << "7. 종료" << endl;
        cout << "8. 지원취소" <<endl;
        cout << "9. 지원"<<endl;
        cout << "메뉴 선택: ";
        cin >> choice;

        switch (choice) {
            case 1:
                signUp();
                break;
            case 2:
                login();
                break;
            case 3:
                logout();
                break;
            case 4:
                registerJobOpening();
                break;
            case 5:
                searchJobOpening();
                break;
            case 6:
                showApplicationDetails();
                break;
            case 7:
                break;
            case 8:
                cancelApplication();
                break;
            case 9:
                selectApplication();
                break;
            default:
                cout << "잘못된 입력입니다. 다시 선택해주세요." << endl;
                break;
        }
    }

    return 0;
}
