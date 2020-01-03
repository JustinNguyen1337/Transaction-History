#include "History_Transaction_definitions.hpp"
#include "project3.hpp"
#include "History.hpp"
#include "Transaction.hpp"

#ifndef MARMOSET_TESTING
int main();
#endif

#ifndef MARMOSET_TESTING
unsigned int Transaction::assigned_trans_id = 0;
int main() {
	History trans_history{};
	trans_history.read_history();
	std::cout << "[Starting history]:" << std::endl;
	trans_history.print();
	std::cout << std::endl;
	trans_history.sort_by_date();
	std::cout << "[Sorted          ]:" << std::endl;
	trans_history.print();
	std::cout << std::endl;
	trans_history.update_acb_cgl();
	trans_history.print();
	std::cout << std::endl;
	std::cout << "[CGL for 2018    ]: " << trans_history.compute_cgl(2018) << std::endl;
	std::cout << "[CGL for 2019    ]: " << trans_history.compute_cgl(2019) << std::endl;

	return 0;
}
#endif


/*VGRO 22 12 2018 Sell 80 2817.600
VGRO 10 01 2018 Buy 150 10300.140
VGRO 11 11 2018 Buy 78 7028.580
VGRO 14 06 2019 Sell 80 4451.200
VGRO 20 10 2019 Buy 100 9011.000
VGRO 24 02 2018 Buy 85 7423.050
VGRO 04 01 2019 Buy 65 3257.150
VGRO 08 08 2018 Buy 43 3367.760
VGRO 16 07 2019 Buy 25 1752.750
VGRO 19 07 2019 Sell 90 6780.600
VGRO 07 05 2019 Buy 65 4557.150
VGRO 08 12 2018 Sell 55 5958.150*/
/*VGRO 22 12 2018 Sell 80 2817.600
VGRO 10 01 2018 Buy 150 10300.140
VGRO 11 11 2018 Buy 78 7028.580
VGRO 24 02 2018 Buy 85 7423.050
VGRO 08 12 2018 Sell 55 5958.150
VGRO 08 08 2018 Buy 43 3367.760*/

/*VGRO 10 01 2018 Buy 150 10300.140
VGRO 24 02 2018 Buy 85 7423.050
VGRO 08 08 2018 Buy 43 3367.760
VGRO 11 11 2018 Buy 78 7028.580
VGRO 08 12 2018 Sell 55 5958.15
VGRO 22 12 2018 Sell 80 2817.600
VGRO 04 01 2019 Buy 65 3257.150
VGRO 07 05 2019 Buy 65 4557.150
VGRO 14 06 2019 Sell 80 4451.200
VGRO 16 07 2019 Buy 25 1752.750
VGRO 19 07 2019 Sell 90 6780.600
VGRO 20 10 2019 Buy 100 9011.000*/
