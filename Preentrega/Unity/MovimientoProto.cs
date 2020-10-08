using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;

public class MovimientoProto : MonoBehaviour
{
    SerialPort puerto = new SerialPort("COM9", 9600);
    int aceZ;
    int aceY;
    int aceZ2;
    int aceY2;
    public GameObject ganastes;
    public GameObject brazo;
    public bool mn = false;

    void Start()
    {
        puerto.Open();
        puerto.ReadTimeout = 1;
        ganastes.SetActive(false);
    }

    // Update is called once per frame
    void Update()
    {
        if (puerto.IsOpen == true)
        {
            try
            {
                moverBrazo(puerto.ReadLine());
            }
            catch (System.Exception)
            {

            }
        }
    }

    public void moverBrazo(string valorBrazo)
    {
        string[] datosBrazo = valorBrazo.Split(char.Parse(","));
        if (datosBrazo.Length == 2)
        {
            aceZ = int.Parse(datosBrazo[0]);
            aceY = int.Parse(datosBrazo[1]);
            
        }
        Debug.Log(aceZ);
        brazo.transform.eulerAngles = new Vector3(aceY, 0, (aceZ * -1));

    }
}
