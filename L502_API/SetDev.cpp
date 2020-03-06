#include "Header.h"

int SetDev(t_l502_hnd& create)
{
	int err = 0;

	//_____���������� ���������� �������
	err = L502_SetLChannelCount(create, 1);
	if (err != L502_ERR_OK)
	{
		cout << "������ ��������� ���������� ���������� �������: " << L502_GetErrorString(err) << endl;
		system("pause");
		return err;
	}

	//_____��������� ������� ���������� �������
	err = L502_SetLChannel(create, 0, 0, L502_LCH_MODE_DIFF, L502_ADC_RANGE_10, 1);
	if (err != L502_ERR_OK)
	{
		cout << "������ ��������� ���������� �������: " << L502_GetErrorString(err) << endl;
		system("pause");
		return err;
	}

	//_____������������� ������ ������ ��������
	L502_SetDmaBufSize(create, L502_DMA_CH_IN | L502_DMA_CH_OUT, ADC_ARRAY_SIZE+5);

	//_____��������� �������� ������� ���
	double f_acq = F_ACQ*pow(10,3);
	L502_SetAdcFreq(create, &f_acq, nullptr);

	//_____������ �������� �� ����������
	err = L502_Configure(create, 0);
	if (err != L502_ERR_OK)
	{
		cout << "������ �������� ��������: " << L502_GetErrorString(err) << endl;
		system("pause");
		return err;
	}

	//_____��������� ������ ������
	err = L502_StreamsEnable(create, L502_STREAM_ADC | L502_STREAM_DAC2);
	if (err != L502_ERR_OK)
	{
		cout << "������ ���������� �������: " << L502_GetErrorString(err) << endl;
		system("pause");
		return err;
	}

	//_____�������� ������
	err = L502_StreamsStart(create);
	if (err != L502_ERR_OK)
	{
		cout << "������ ������ �������: " << L502_GetErrorString(err) << endl;
		system("pause");
		return err;
	}

	return err;
}