void Boss::Insert_manager()                    //添加经理
{
	list<Manager> Link1;
	Manager manager;
	char ch;
	char man[100];
	while(1)	
	{
		const char *server = "localhost";
		const char *user = "root";
		const char *password = "930823";
		const char *database = "company";
		//初始化数据库句柄
		conn = mysql_init(NULL);
		//链接数据库
		if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
		{
			fprintf(stderr,"%s\n",mysql_error(conn));
			exit(1);
		}
		mysql_set_character_set(conn,"utf8");  //设置字符集
		//while(l != Link1.end())
		while(1)
		{        Manager manager;                                               //将信息添加到Link中

			cout<<"                              请输入要添加的经理的信息:"<<endl;
			cout<<"编号:";	
			cin>>manager.id;
			cout<<"姓名:";
			cin>>manager.name;
			cout<<"密码:";
			cin>>manager.password;
			cout<<"级别:";
			cin>>manager.rank;
			cout<<"工资:";
			cin>>manager.wage;
			Link1.push_back(manager);
			cout<<"                              是否继续添加[y/n]"<<endl;
			while(getchar() != '\n');
			ch = getchar();
			if('n' == ch)
				break;
		}
		cout<<"                              确定退出吗[y/n]"<<endl;
		while(getchar() != '\n');
		ch = getchar();
		if('y' == ch)
		{	list<Manager>::iterator l = Link1.begin();
			while(l != Link1.end())                                  //将信息添加到数据库里（容器--->数据库）
			{	

				sprintf(man,"insert into members(id,name,password,rank,wage) values (%d,'%s',%d,%d,%f)",l->id,l->name,l->password,l->rank,l->wage);                                                      //产生中间的那句话并写到man中
				if(mysql_query(conn,man))   //发送SQL语句，成功返回0
				{
					fprintf(stderr,"%s\n",mysql_error(conn));
					exit(1);
				}
				l++;
			}		
			//释放结果集使用的内存
			mysql_free_result(res);
			//关闭数据库链接
			mysql_close(conn);

			break;	
		}
		//释放结果集
		//				mysql_free_result(res);
		//关闭数据库链接
		//			mysql_close(conn);
	}
	return ;
}

