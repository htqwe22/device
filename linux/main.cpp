#include <JSONObject.h>


int main(int argc,char **argv){
	/*C ���Թ���*/
	JSONObject root("{\"Cmd\":\"ACSET\",\"value\":5}");
	cout<< root.toString()<<endl;
	cout<<root.getNumber("value")<<" "<<root.getString("Cmd")<<endl;
	cout<< root.toString()<<endl;

	/*String ����*/
	JSONObject root3(root.toString());
	cout<< root3.toString()<<endl;

	/*��������*/
	JSONObject root4(root3);
	cout<< root4.toString()<<endl;
	root4.putNumber("abc",60);
	root4.putString("keyi","hello");
	
	cout<< root4.toString()<<endl;
	
	cout<< root4.toString()<<endl;
	cout<<root4.getNumber("value")<<" "<<root4.getString("Cmd")<<endl;

	/*��ֵ����*/
	JSONObject root5 = root4;
	cout<<root5.toString()<<endl;
	root5 = root3;
	cout<<root5<<endl;
	root5.putString("HELLO","world");
	cout<<"==============================="<<endl;
	cout<<root5<<endl;
	return 0;
}


