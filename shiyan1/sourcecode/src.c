#include<stdio.h>
#include<string.h>
#include<stdlib.h>


typedef struct
{
	int c_custkey;    	   //顾客编号
	char c_mkgsegment[20]; //对应的某个市场部门
}customer;				   //顾客结构体 

typedef struct
{
	int o_orderkey;    	 //订单号 
	int o_custkey;    	 //顾客编号
	char o_orderdate[10];//订货日期 
}orders;				 //订单


typedef struct
{
	int l_orderkey;//订单号
	char o_orderdate[10];//订货日期 
	double l_extendedprice;//额外价格
}select_result;

typedef struct
{
	int l_orderkey;//订单号
	double l_extendedprice;//额外价格
	char l_shipdate[10];//发货日期 
}lineitem; //商品信息 

customer * read_customer_txt() 
{
	FILE * fp;
	customer *a=NULL;
	ap = (customer *)malloc(101*sizeof(customer));
	int i=0;
	char b;
	fp = fopen("customer.txt","r");
	if(NULL==fp)
	{
		printf("cannot open customer.txt!");
		return NULL;
	}
	while(!feof(fp))
	{	
		
		fscanf(fp,"%d%c%s",&a[i].c_custkey,&b,&a[i].c_mkgsegment);
		
		i++;
	}
	fclose(fp);
	return ap;
}
	orders * read_orders_txt()
{
	int i =0; 
	orders * ap=NULL;
	ap = (orders * )malloc(4001*sizeof(orders));
	char b,c;
	long long d;
	FILE *fp;
	fp = fopen("orders.txt","r");
	if(fp == NULL)
	{
		printf("cannot open orders.txt!");
		return NULL;
	}
	while(!feof(fp))
	{	
		
		fscanf(fp,"%d%c%lld%c%s",&a[i].o_orderkey,&b,&d,&c,&a[i].o_orderdate);
		ap[i].o_custkey=d%100;
		
		i++;
	}
	fclose(fp);
	return ap;
}

	lineitem * read_lineitem_txt()
{
	FILE * fp;
	lineitem * l=NULL;
	l = (lineitem *)malloc(1001*sizeof(lineitem));
	int i=0;
	char b,c;
	fp = fopen("lineitem.txt","r");
	if(fp==NULL)
	{
		printf("cannot open lineitem.txt!");
		return NULL;
	}
	while(!feof(fp))
	{
		
		fscanf(fp,"%d%c%lf%c%s",&l[i].l_orderkey,&c,&l[i].l_extendedprice,&b,&l[i].l_shipdate);
		
		i++;
	}
	fclose(fp);
	return l; 
}

	select_result * Select(customer * cus,orders * ord,lineitem * item,char * order_date,char * ship_date,char * mktsegment)
{
	
	select_result * abc=NULL;
    abc=(select_result *)malloc(4001*sizeof(select_result));
    int i,j,k;
    int n=0;
    for(i=0;i<100;i++)
    {
     if(strcmp(cus[i].c_mkgsegment,mktsegment)==0)
        {
	 for(j=0;j<4000;j++)
            {
     if(cus[i].c_custkey==ord[j].o_custkey&&strcmp(ord[j].o_orderdate,order_date)<0)
 {
     for(k=0;k<1000000;k++) 
{
      if(ord[j].o_orderkey==item[k].l_orderkey&&strcmp(item[k].l_shipdate,ship_date)>0)
 {
     abc[n].l_extendedprice=item[k].l_extendedprice;
     strcpy(abc[n].o_orderdate,ord[j].o_orderdate);
      abc[n].l_orderkey=item[k].l_orderkey;
                          
     if(n>0 && abc[n-1].l_orderkey==abc[n].l_orderkey)
  {
       abc[n-1].l_extendedprice+=abc[n].l_extendedprice;
       n--;
                               
}
        n++;
}
}
 }
}
}
 }
    return abc;

	
}

	int change_argv_to_number(char s[])//将命令行里读入的数字字符串转化为整形数字 
{
	int i=0;
	int number=0;
	while(s[i]!='\0')
	{
	if(i==0)
		number = (s[i]-48);
	else
			number = number*10 + (s[i]-48);
		
	i++;
	}
	return number;
}

	int main(int argc,char * argv[]) 
{
	int i,j;
	int num;
	
	int limit=3;
	char order_date[15];
	char ship_date[15];
	char mktsegment[25];
	select_result *result=NULL;
	customer * cus = NULL;//指向客户表的指针 
	orders * ord = NULL;//指向订单表的指针 
	lineitem * item = NULL;//指向 产品表的指针 
	cus = read_customer_txt();//读取customer.txt的内容 ，导入客户表 
	ord = read_orders_txt();//读取orders.txt的内容 ，导入订单表 
	item = read_lineitem_txt();//读取lineitem.txt的内容 ，导入产品表 
	num = change_argv_to_number(argv[4]);//总共计算的次数
	
	for(i=0;num>0;num--,i=i+4)
	{
		strcpy(mktsegment,argv[5+i]);
		strcpy(ship_date,argv[7+i]);
		limit = change_argv_to_number(argv[8+i]);
		//printf("%d	mktsegment:%s	order_date:%s	ship_date:%s	limit:%d\n",num,mktsegment,order_date,ship_date,limit);
		strcpy(order_date,argv[6+i]);
		result=Select(cus,ord,item,order_date,ship_date,mktsegment);
		printf("l_orderkey|o_orderdate|revenue\n");
		for(j=0;j<limit;j++)
		{
			if(result[j].l_extendedprice==0)
				printf("null      |null       |null   \n");
			else
				printf("%-10d|%-11s|%-20.2lf\n",result[j].l_orderkey,result[j].o_orderdate,result[j].l_extendedprice);
		}
		free(result);
		result = NULL;
	} 
	
	
	return 0;
}
