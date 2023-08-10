#include "pid.h"
PID motor_speed_pid[8];
double PIDCalc( PID *pp, double current_value );
int16_t motor_out[8];
extern int16_t motor_speed_current[8];
void pid_ini(void)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		motor_speed_pid[i].uk_1=0.0;
		motor_speed_pid[i].SetValue=00.0;
		motor_speed_pid[i].Kp=2.5 ; //10  Proportional Const
		motor_speed_pid[i].Ki=0.3; //0.5   Integral Const
		motor_speed_pid[i].Kd=0.0; //  Derivative Const
		motor_speed_pid[i].ek_1=0.0; // Error[-1]
		motor_speed_pid[i].ek_2=0.0; // Error[-2]
		motor_speed_pid[i].max_limit=16384.0; // value<=Max_limit
		motor_speed_pid[i].min_limit=-16384.0; //
	}
	//motor_speed_pid[0]->Kp=10 ; //  Proportional Const
//	motor_speed_pid[1]->Kp=10 ; //  Proportional Const
//	motor_speed_pid[2]->Kp=p10 ; //  Proportional Const
//	motor_speed_pid[3]->Kp=10 ; //  Proportional Const
//	motor_speed_pid[4]->Kp=10 ; //  Proportional Const
//	motor_speed_pid[5]->Kp=10 ; //  Proportional Const
//	motor_speed_pid[6]->Kp=10 ; //  Proportional Const
//	motor_speed_pid[7]->Kp=10 ; //  Proportional Const		
}
void pid_speed_Calc(void)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		motor_out[i]=(int16_t )PIDCalc(&motor_speed_pid[i],motor_speed_current[i]);	
	}
}
//pid
double PIDCalc( PID *pp, double current_value )
{
	//dlt_u(k)=Kp[e(k)-e(k-1)]+Kie(k)+Kd[e(k)-2e(k-1)+e(k-2)]
	//u(k)=u(k-1)+dlt_u(k)
	double ek,dlt_uk,uk;
	ek = pp->SetValue - current_value;   
	dlt_uk=pp->Kp*(ek-pp->ek_1)+pp->Ki*ek+pp->Kd*(ek-2*pp->ek_1+pp->ek_2);
	uk=pp->uk_1+dlt_uk;
	if(uk<pp->min_limit) uk=pp->min_limit;
	if(uk>pp->max_limit) uk=pp->max_limit;
	pp->ek_2=pp->ek_1;
	pp->ek_1=ek;
	pp->uk_1=uk;
	return uk;
}
