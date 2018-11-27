#include"ui.h"
int main()
{   
	int ret;
	STNODE *head=NULL;
	head=readfiletolist("dictionary.txt");
    while(1)
    {
    	ret=MainUI();
	    switch(ret)
	    {
		    case 1:
		    	head=AdddicinfoUI(head);
            	rethome();
		    	break;
		    case 2:
		    	head=deletedicinfo(head);
            	rethome();
		    	break;
	        case 3:
		    	head=Modifydicinfo(head);
                rethome();
		    	break;
            case 4:
                searchnameorID(head);
		    	break; 
			case 5:
                showdicinfo(head);
                rethome();
		    	break;  
        }
             if(0==ret)
             	confirmsave(head);
	}
    return 0;
}

