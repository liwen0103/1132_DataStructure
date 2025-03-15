#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Player {  /*玩家結構資料型態，包含string類型的玩家名稱以及int類型的玩家分數*/
    string name;
    int score;
    int aceCount; // 記錄A的數量，方便處理A作為1或11點
};

int drawCard() {
    int card = rand() % 13 + 1; /*發牌功能，呼叫一次發一張數值在1-13之間的牌*/
    if (card > 10) return 10; // J, Q, K 都是 10 點
    return card; // 其他牌保持原數值
}

// 計算點數，處理 A (Ace) 可以是 1 或 11 的情況
void calculateScore(Player* player, int card) {
    if (card == 1) {
        player->aceCount++;
        player->score += 11;
    } else {
        player->score += card;
    }
    while (player->score > 21 && player->aceCount > 0) {
        player->score -= 10; // 如果總分超過21，將A的值從11調整為1
        player->aceCount--; // A的數量減少，因為其中一個A已經從11變為1
    }
}

// 初始化玩家
void initializePlayer(Player* player, string name) {
    /*利用上面的結構變數，達到完成初始化玩家並且同時發兩張初始手牌*/
    player->name = name;
    player->score = 0;
    player->aceCount = 0;
    calculateScore(player, drawCard());
    calculateScore(player, drawCard());
}

// 顯示玩家分數
void displayScore(Player* player) {
    /*顯示玩家當前的手牌點數*/
    cout << player->name << " 的目前分數: " << player->score << endl;
}

// 玩家回合
void playerTurn(Player* player) {
    char choice;
    while (player->score < 21) {
        cout << "要抽牌嗎？(h = 抽, s = 停) : ";
        cin >> choice;
        if (choice == 'h') {
            int newCard = drawCard();
            /*抽牌提示；宣告一個變數再呼叫抽牌函數*/
            calculateScore(player, newCard);
            /*將新抽到的手牌點數加上原本玩家擁有的手牌點數，並打印出來當前玩家手牌總點數*/
            cout << player->name << " 抽到了 " << newCard << "，總分: " << player->score << endl;
            if (player->score > 21) {
                cout << player->name << " 爆掉了！遊戲結束。\n";
                return;
            }
        } else if (choice == 's') {
            break;
        }
    }
}

// 莊家回合
void dealerTurn(Player* dealer) {
    while (dealer->score < 17) { // 莊家至少要到 17 點
        int newCard = drawCard();
        /*如果莊家點數小於17，則至少持續增加手牌值到莊家手牌點數大於等於17，並將莊家手牌點數打印出來*/
        calculateScore(dealer, newCard);
        cout << "莊家抽到 " << newCard << " 點，目前總分: " << dealer->score << endl;
        if (dealer->score > 21) { // 如果莊家超過 21 點
            cout << "莊家爆了！玩家獲勝！" << endl;
            return; // 遊戲結束
        }
    }
}

// 判斷勝負
void determineWinner(Player* player, Player* dealer) {
    if (player->score > 21) {
        cout << "你爆了！莊家獲勝！\n";
    } else if (dealer->score > 21 || player->score > dealer->score) {
        cout << "你贏了！!\n";
    } else if (player->score == dealer->score) {
        cout << "平手！\n";
    } else {
        cout << "莊家贏了！\n";
    }
}

// 主程式
int main() {
    srand(time(0)); // 設定隨機數種子

    Player player, dealer;
    initializePlayer(&player, "玩家");
    initializePlayer(&dealer, "莊家");

    displayScore(&player);
    playerTurn(&player);

    if (player.score <= 21) { // 如果沒爆才讓莊家回合
        cout << "\n莊家回合...\n";
        displayScore(&dealer);
        dealerTurn(&dealer);
        determineWinner(&player, &dealer);
    }

    return 0;
}
