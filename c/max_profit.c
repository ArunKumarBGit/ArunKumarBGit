#include <stdio.h>

int 
maxProfit (int* prices, int sz)
{
    int buy_price   = 0;
    int sell_price  = 0;
    int profit      = 0;
    int max_profit  = 0;
    int i           = 0;
    
    for (i = 0; i < sz; i++) {
        if ((i == 0)) {
            buy_price = prices[i];
            continue;
        }
        
        if (prices[i] < buy_price) {
            buy_price = prices[i];
            continue;
        }
        
        if ((prices[i] - buy_price) > profit) {
            sell_price = prices[i];
            profit = sell_price - buy_price;
            
            if (profit > max_profit) {
                max_profit = profit;
            }
        }
    }
    
    return(max_profit);
}


int
main (void)
{
    int prices[] = {2,1,2,1,0,1,2};

    printf("\n\nMaximum profit = '%d'\n\n",
           maxProfit(prices, (sizeof(prices)/sizeof(prices[0]))));

    return(0);
}
