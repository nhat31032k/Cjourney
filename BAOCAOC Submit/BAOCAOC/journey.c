#include "defs.h"
#include <math.h>

struct journey{
	int meetNina;
	int mythrilArmor;
	int avatarEffect;
	int titanHelp;
	int countTitanWin;
	int diamondList[1000]; //danh sach kim cuong kiem duoc
};

struct journey theJourney;
struct musketeer braveMusketeer;

void createZeroArray(int arr[], int arrSize){
	int i;
	for(i = 0; i <= arrSize; i++){
		arr[i] = 0;
	}
}

//Tim so nguyen to nho hon va gan R nhat
int findPrimeNumSmallerR(int R){
	int P = 2;
	int primeList[5] = {2, 3, 5, 7, 11};
	int i;
	
	for(i = 0; i < 5; i++){
		if(primeList[i] >= R){
			return P;
		}
		P = primeList[i];
	}
	return P;
}

//Kiem tra so nguyen to
int checkPrimeNumber(int num){
	if(num <= 1){
		return -1;
	}
	
	int i;
	for(i = 2; i < num/2; i++){
		if(num % i == 0){
			return -1;
		}
	}
	return 1;
}

//Kiem tra 2 so nguyen to cung nhau
int checkCoPrime(int numA, int numB){
	if(numA > 0 && numB > 0){
		while(numA != numB) {
			if(numA > numB) {
				numA = numA - numB;
			}
			else {
				numB = numB - numA;
			}
		}
		
		if(numA == 1) {
			return 1;
		}
		else {
			return 0;
		}
	}
	return 0;
}


int fibonaci(int n)
{
    int f0 = 1;
    int f1 = 1;
    int f, i;
    if(n < 2){
    	return 1;
	}  
    i = 1;
    while(i < n)
    {
        f = f0 + f1;
        f0 = f1;
        f1 = f;
        i++;
    }
    return f;
}
//Ham kiem tra so Fibonacci
int checkFibonacci(int value)
{
    int i = 0;
    while(value > fibonaci(i)){
        ++i;
    }
    if(value == fibonaci(i)){
    	return 1;
	}
    return 0;
}

//Ham tra ve uoc so chung lon nhat cua 2 so nguyen
int getGreatestCommonDivisor(int a, int b) {
    if(b == 0){
    	return a;
	}
    return getGreatestCommonDivisor(b, a % b);
}
//Them kim cuong
void addDiamondToList(int diamondEventNum){
	int i;
	for(i = 0; i < 1000; i++){
		if(theJourney.diamondList[i] == 0){
			theJourney.diamondList[i] = diamondEventNum;
			int numDiamondType = diamondEventNum /100;
			if(numDiamondType == 1){
				braveMusketeer.nBlueDiamonds++;
			}
			else if(numDiamondType == 2){
				braveMusketeer.nRedDiamonds++;
			}
			break;
		}
	}
}

//Bo kim cuong theo thu tu moi nhat duoc gan day tro ve truoc
//numberDiamond la so kim cuong se mat
//diamondType la loai kim cuong: 1 la kim cuong xanh, 2 kim cuong do
void removeDiamondFromList(int numberDiamond, int diamondType){
	int i = braveMusketeer.nBlueDiamonds + braveMusketeer.nRedDiamonds - 1;
	int diamondTempList[1000];
	
	createZeroArray(diamondTempList, 1000);
	while(numberDiamond > 0 && i > 0){
		int numDiamond = theJourney.diamondList[i]/100;
		if(numDiamond == 1 && numDiamond == diamondType){
			braveMusketeer.nBlueDiamonds--;
			theJourney.diamondList[i] = 0;
			numberDiamond--;
		}
		else if(numDiamond == 2 && numDiamond == diamondType){
			braveMusketeer.nRedDiamonds--;
			theJourney.diamondList[i] = 0;
			numberDiamond--;
		}
		i--;
	}
	int j;
	for(i = 0, j = 0; i < 1000; i++){
		if(theJourney.diamondList[i] != 0){
			diamondTempList[j] = theJourney.diamondList[i];
			j++;
		}
		else{
			continue;
		}
	}
	for(i = 0; i < 1000; i++){
		theJourney.diamondList[i] = diamondTempList[i];
	}
}

//Tang HP
void increaseHealth(int XY){
	if (braveMusketeer.nHealthPoint + XY <= braveMusketeer.HP){
		braveMusketeer.nHealthPoint = braveMusketeer.nHealthPoint + XY;
	}
	else{
		braveMusketeer.nHealthPoint = braveMusketeer.HP;
	}
}
//Giam HP
void decreaseHealth(int R, int XY){
	//Neu co giap Mythril
	if(theJourney.mythrilArmor == 1){
		float a = (R+1)/(pow(2, R));
		XY = round(XY * a);
	}
	if (braveMusketeer.nHealthPoint - XY < 0){
		braveMusketeer.nHealthPoint = 0;
	}
	else{
		braveMusketeer.nHealthPoint = braveMusketeer.nHealthPoint - XY;
	}
}
//Tang Coin
void increaseCoin(int XY){
	if (braveMusketeer.nGoldCoin + XY <= 999){
		braveMusketeer.nGoldCoin = braveMusketeer.nGoldCoin + XY;
	}
	else{
		braveMusketeer.nGoldCoin = 999;
	}
}
//Giam Coin
void decreaseCoin(int XY){
	braveMusketeer.nGoldCoin = braveMusketeer.nGoldCoin - XY;
}

//P la so coin cho 1 hp
void restoreHealthByCoin(int XY, int P){
	int maxRestorePoint = XY;
	
	while(1){
		if(maxRestorePoint <= 0 || braveMusketeer.nGoldCoin - P <= 0 || braveMusketeer.nHealthPoint >= braveMusketeer.HP){
			break;
		}
		maxRestorePoint--;
		braveMusketeer.nGoldCoin = braveMusketeer.nGoldCoin - P;
		braveMusketeer.nHealthPoint++;
	}
}

//Gap doi ve binh va titan bat dau tu vi tri nhat dinh
//Tra ve so ke dich duoc gap doi
int duplicateEnemy(int arrEvent[], int nEvent, int currentIndex){
	int i, j;
	int tempArray[1000];
	int countDuplicate = 0;
	
	createZeroArray(tempArray, 1000);
	for(i = currentIndex, j = 0; i <= nEvent; i++, j++){
		int numEvent = arrEvent[i] / 100;
		if(numEvent == 4 || numEvent == 7){
			tempArray[j] = arrEvent[i];
			j++;
			
			countDuplicate++;
		}
		tempArray[j] = arrEvent[i];
	}
	nEvent = nEvent + countDuplicate;
	for(i = currentIndex, j = 0; i <= nEvent; i++, j++){
		arrEvent[i] = tempArray[j];
	}
	return countDuplicate;
}

//Xoa bo ve binh va titan bi gap doi tu vi tri nhat dinh
//Tra ve so ke dich da xoa
int removeDuplicateEnemy(int arrEvent[], int nEvent, int currentIndex){
	int i, j;
	int tempArray[1000];
	int countRemovedElement = 0;
	int duplicateFlag = 0;

	createZeroArray(tempArray, 1000);
	for(i = currentIndex, j = 0; i <= nEvent; i++){
		int numEvent = arrEvent[i] / 100;
		if(numEvent == 4 || numEvent == 7){
			if(duplicateFlag == 0){
				tempArray[j] = arrEvent[i];
				duplicateFlag = 1;
				j++;
			}
			else{
				countRemovedElement++;
				duplicateFlag = 0;
			}
		}
		else{
			tempArray[j] = arrEvent[i];
			j++;
		}
		
	}
	for(i = currentIndex, j = 0; i <= nEvent; i++, j++){
		arrEvent[i] = tempArray[j];
	}
	return countRemovedElement;
}

//Kha nang bo qua tran dau khi gap bat loi cua Aramis
//1 se bo qua tran danh; 0 se chien dau
int dodgeTheFight(int R, int XY){
	//Neu co giap Mythril
	if(theJourney.mythrilArmor == 1){
		float a = (R+1)/(pow(2, R));
		XY = round(XY * a);
	}
	if (braveMusketeer.nHealthPoint - XY < 1){
		return 1;
	}
	else{
		return 0;
	}
}

//Tinh mainResult 
int calculateMainResult(){
	int mainResult = 0;
	int j = 0;
	int totalDiamondPrice = 0;
	while(1){
		if(theJourney.diamondList[j] == 0){
			break;
		}
		int numDiamond = theJourney.diamondList[j];
		int priceDiamond = numDiamond % 100;
		
		totalDiamondPrice = totalDiamondPrice + priceDiamond;
		j++;
	}
	mainResult = braveMusketeer.nHealthPoint + braveMusketeer.nGoldCoin + totalDiamondPrice;
	
	return mainResult;
}

int calculate(struct musketeer theMusketeer, int R, int N, int nEvent, int* arrEvent)
{
	int nOut = 0;
	int i;
	theJourney.meetNina = 0;
	theJourney.mythrilArmor = 0;
	theJourney.avatarEffect = 0;
	theJourney.titanHelp = 0;
	theJourney.countTitanWin = 0;
	
	createZeroArray(theJourney.diamondList, 1000);
	
	//Kiem tra co phai d’Artagnan khong
	if(theMusketeer.ID == 1){
		braveMusketeer.ID = 1;
		braveMusketeer.HP = 999;
		braveMusketeer.nHealthPoint = 999;
	}
	//Kiem tra co phai Athos khong
	else if(theMusketeer.ID == 2){
		braveMusketeer.ID = 2;
		braveMusketeer.HP = 900;
		braveMusketeer.nHealthPoint = 900;
	}
	//Kiem tra co phai Porthos khong
	else if(theMusketeer.ID == 3){
		braveMusketeer.ID = 3;
		braveMusketeer.HP = 888;
		braveMusketeer.nHealthPoint = 888;
	}
	//Kiem tra co phai Aramis khong
	else if(theMusketeer.ID == 4){
		braveMusketeer.ID = 4;
		braveMusketeer.HP = 777;
		braveMusketeer.nHealthPoint = 777;
	}
	braveMusketeer.nGoldCoin = theMusketeer.nGoldCoin;
	braveMusketeer.nBlueDiamonds = 0;
	braveMusketeer.nRedDiamonds = 0;

	//Vong lap kiem tra day su kien Ei
	for(i = 1; i <= nEvent; i++){
    	int numEvent = arrEvent[i] / 100;
    	int XY = arrEvent[i] % 100;
    	
    	//Su kien nhat duoc mot hat kim cuong xanh
    	//XY la gia tien
    	if(numEvent == 1){
    		//Porthos se ban kiem cuong xanh ngay khi co duoc
    		if(braveMusketeer.ID == 3){
    			increaseCoin(XY);
			}
			else{
				addDiamondToList(arrEvent[i]);
			}
		}
		
		//Su kien nhat duoc mot hat kim cuong do
    	//XY la gia tien
    	else if(numEvent == 2){
    		addDiamondToList(arrEvent[i]);
		}
		
		//Su kien di den nha tro
    	//XY la so tien toi da duoc phep dung de hoi HP
    	else if(numEvent == 3){
    		int P = 1;
    		
    		if(braveMusketeer.ID == 3){
    			if(R >= 3 && braveMusketeer.nGoldCoin > 2){
    				P = findPrimeNumSmallerR(R);
    				int maxRestorePoint = XY/P;
    				restoreHealthByCoin(maxRestorePoint, P);
				}
			}
			else{
				restoreHealthByCoin(XY, P);
			}
		}
		
		//Su kien bi ve binh mai phuc
    	//XY la so tien thuong khi thang tran va so mau ton that khi thua tran
    	else if(numEvent == 4){
			int h1 = XY * R;
			int h2 = (braveMusketeer.nHealthPoint + h1) % (100 + R);
		
			//Kiem tra co phai Porthos
			if(braveMusketeer.ID == 3 && theJourney.titanHelp > 0){
				theJourney.titanHelp--;
			}
			else{
				//Kiem tra co phai Athos
				if(braveMusketeer.ID == 2){
					if(checkPrimeNumber(h2) == 1 && h2 > R){
						decreaseHealth(R, XY);
					}
				}
				else{
					//Thang tran va nhan XY dong tien
					if(braveMusketeer.nHealthPoint >= h1){
						increaseCoin(XY);
					}
					//Thua tran va mat XY HP
					else if(h2 == 0 || braveMusketeer.nHealthPoint < h1){
						//Kiem tra Musketeer do khong bo qua tran danh
						if( (braveMusketeer.ID != 4) || (braveMusketeer.ID == 4 && dodgeTheFight(R, XY) == 0) ){
							decreaseHealth(R, XY);
						}
					}
				}
			}
		}
		
		//Su kien gap lai buon vui tinh Nina de Rings
    	//XY la gia tri phan thuong hoac bi thuong
		else if(numEvent == 5){
			if(theJourney.meetNina == 0){
				int h1 = XY * R;
				int h2 = (braveMusketeer.nHealthPoint + h1) % (100 + R);
				
				//Thang tran Nina
				if(braveMusketeer.nHealthPoint >= h1){
					//Neu so kim cuong do va xanh la so nguyen to cung nhau
					if( checkCoPrime(braveMusketeer.nBlueDiamonds, braveMusketeer.nRedDiamonds) == 1){
						theJourney.mythrilArmor = 1;
					}
					else{
						//Neu la Porthos se nhan duoc mot kim cuong do
						if(braveMusketeer.ID == 3){
							addDiamondToList(200 + XY);
						}
						else{
							addDiamondToList(100 + XY);
						}
					}
				}
				//Thua Nina
				else if(h2 == 0 || braveMusketeer.nHealthPoint < h1){
					if( (braveMusketeer.ID != 4) || (braveMusketeer.ID == 4 && dodgeTheFight(R, XY) == 0) ){
						decreaseHealth(R, XY);
						decreaseCoin(braveMusketeer.nGoldCoin/2);
					}
				}
				theJourney.meetNina = 1;
			}
		}
		
		//Su kien gap Avatar
    	//XY la gia tri luong HP tang
		else if(numEvent == 6){
			//Thoa dieu kien Avatar
			if(braveMusketeer.nBlueDiamonds >= braveMusketeer.nRedDiamonds){
				//Xoa hieu ung Avatar neu co
				if(theJourney.avatarEffect == 1){
					theJourney.avatarEffect = 0;
					//Xoa hieu ung avatar
					//Cap nhat lai nEvent
					nEvent = nEvent + removeDuplicateEnemy(arrEvent, nEvent, i);
				}
				increaseHealth(XY);
			}
			else{
				//Ap dung hieu ung Avatar neu chua co
				if(theJourney.avatarEffect == 0){
					theJourney.avatarEffect = 1;
					//Nhan doi so luong ke thu
					//Cap nhat lai nEvent
					nEvent = nEvent + duplicateEnemy(arrEvent, nEvent, i);
				}
				
			}
		}
		
		//Su kien gap Titan
    	//Ei la gia tri luong HP mat khi thua tran
		else if(numEvent == 7){
			int h1 = XY * R;
			int h2 = (braveMusketeer.nHealthPoint + h1) % (100 + R);
		
			//Kiem tra co phai Porthos
			if(braveMusketeer.ID == 3){
				theJourney.titanHelp = 3;
			}
			else{
				//Thang tran va dem so lan thang Titan
				if(braveMusketeer.nHealthPoint >= h1){
					theJourney.countTitanWin++;
				}
				//Thua tran va mat Ei HP
				else if(h2 == 0 || braveMusketeer.nHealthPoint < h1){
					if( (braveMusketeer.ID != 4) || (braveMusketeer.ID == 4 && dodgeTheFight(R, arrEvent[i]) == 0) ){
						decreaseHealth(R, arrEvent[i]);
					}
				}
			}
		}
		
		//Su kien gap ba tuoc Milady
    	//Uoc so chung XY la so kim cuong bi mat
		else if(numEvent == 8){
			//Kiem tra co phai d’Artagnan
			if(braveMusketeer.ID == 1){
				return nOut = -1;
			}
			//Kiem tra co phai Athos
			else if(braveMusketeer.ID == 2){
				increaseCoin(999);
			}
			//Kiem tra co phai Porthos
			else if(braveMusketeer.ID == 3 && braveMusketeer.nHealthPoint <= 700){
				int a = XY/10;
				int b = XY%10;
				if(a > 0 && b > 0){
					int numberDiamond = getGreatestCommonDivisor(a, b);
					removeDiamondFromList(numberDiamond, 2);
				}
			}
			//Kiem tra co phai Aramis
			else if(braveMusketeer.ID == 4 && braveMusketeer.nHealthPoint <= 700){
				int a = XY/10;
				int b = XY%10;
				if(a > 0 && b > 0){
					int numberDiamond = getGreatestCommonDivisor(a, b);
					removeDiamondFromList(numberDiamond, 1);
				}
			}
		}
		
		//Su kien gap Paladin Lancelot do te tuong Richelieu trieu hoi
    	//Ei la dieu kien giao dau
		else if(numEvent == 9){
			if(checkFibonacci(i) == 1){
				int h1 = XY * R;
				int h2 = (braveMusketeer.nHealthPoint + h1) % (100 + R);
				
				//Thang tran va nhan thuong
				if(braveMusketeer.nHealthPoint >= h1){
					increaseHealth(braveMusketeer.HP);
					increaseCoin(999);
				}
				//Thua tran va ket thuc hanh trinh
				else if(h2 == 0 || braveMusketeer.nHealthPoint < h1){
					return nOut = -1;
				}
			}
			else{
				return nOut = -1;
			}
		}
		
		//Kiem tra cac dieu kien ket thuc
		//Khi so kim cuong du yeu cau hoac da danh bai 3 titan
		if(braveMusketeer.nBlueDiamonds + braveMusketeer.nRedDiamonds >= N || theJourney.countTitanWin == 3){
			nOut = calculateMainResult();
			return nOut;
		}
		if(braveMusketeer.nHealthPoint <= 0 || braveMusketeer.nGoldCoin < 0){
			return -1;
		}
		if(i == nEvent && braveMusketeer.nBlueDiamonds + braveMusketeer.nRedDiamonds < N){
			return nOut = 0;
		}
    }
        
	return nOut;
}
