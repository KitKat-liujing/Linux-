#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/usr/include/mysql/mysql.h"
 
int main(int argc, char *argv[])
{
MYSQL my_connection;
MYSQL_RES *res_ptr;   /*指向检索的结果存放地址的指针*/
MYSQL_ROW sqlrow;     /*返回的记录信息*/
MYSQL_FIELD *fd;      /*字段结构指针*/
char aszflds[25][25]; /*用来存放各字段名*/
char buf[100]={0};
int res,res1;             /*执行查询操作后的返回标志*/
int i,j,k;
int flag=0;
int flagnum=0;

//初始化MYSQL结构
mysql_init(&my_connection);

//连接数据库
if (mysql_real_connect(&my_connection, "192.168.1.211", "jyj", "654321","student",0,NULL,CLIENT_FOUND_ROWS))
{

//数据库查询
    res = mysql_query(&my_connection, "select name,passwd from user");

    if (res)
    {
        printf("SELECT error:%s\n",mysql_error(&my_connection));
    }
    else
    {
/*将查询的全部结果读取到客户端*/
       res_ptr=mysql_store_result(&my_connection);
       if(res_ptr)
       {
              /*取得各字段名*/
              for(i=0;fd=mysql_fetch_field(res_ptr);i++)
                     strcpy(aszflds[i],fd->name);
              /*输出各条记录*/
              j=mysql_num_fields(res_ptr);
	      //判断用户是否存在
              while((sqlrow=mysql_fetch_row(res_ptr)))
              {
					 	if(!strcmp(sqlrow[0],argv[1])){
							flag=1;
							flagnum++;
							//判断用户密码是否输入正确
							if(!strcmp(sqlrow[1],argv[2])){
								if(flagnum==1)
									printf("load successfully!\n");
							}
							else
								if(flagnum==1)
									printf("passwd is error!\n");
						}
							
              }

			  if(flag==1)
			  	flag=0;
			  else
				printf("the user doesn't exist!\n");
       }
	//释放结果资源
       mysql_free_result(res_ptr);
      }
	//关闭数据库连接
    mysql_close(&my_connection);
}

else
{
    fprintf(stderr, "Connection failed\n");

    if (mysql_errno(&my_connection))
    {
        fprintf(stderr, "Connection error %d: %s\n",
        mysql_errno(&my_connection),
        mysql_error(&my_connection));
        }
}
    return EXIT_SUCCESS;
	}
