#include "spi.h"
#include "filter.h"
#include "spi.h"
/*
�޷������˲���
*/

//���ܺ�������������������
unsigned int num_sub( unsigned int a, unsigned int b )
{
    return ( a >= b ? ( a - b ) : ( b - a ) );
}
//�˲����� 
unsigned int filter10( void )
{
    unsigned int count = 0;
    unsigned int new_value = 0;
    unsigned int last_value = 0;
    new_value = GetLTC2500Valuesg();
    if( num_sub( new_value, last_value ) < A )
    {
        new_value = new_value;	//���С��A
    }
    else
    {
        new_value = last_value;	//������A
    }
    
    
//    while( new_value !=  last_value)	//С��A�����
//    {
//        count++;
//        if( count >= N )
//        {
//            last_value = new_value;
//            return new_value;
//        }
//        new_value = GetLTC2500Valuesg();
//        if( num_sub( new_value, last_value ) < A )
//        {
//            new_value = new_value;
//        }
//        else
//        {
//            new_value = last_value;
//        }
//    }
    return new_value;
}

