using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;

public class MovimientoCuerpo : MonoBehaviour
{
    SerialPort puerto = new SerialPort("COM5", 9600);
    int aceZ;
    int aceY;
    int aceZ2;
    int aceY2;
    public GameObject ganastes;
    public GameObject brazo;
    public GameObject pierna;
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
        if (datosBrazo.Length == 4)
        {
            aceZ = int.Parse(datosBrazo[0]);
            aceY = int.Parse(datosBrazo[1]);
            aceZ2 = int.Parse(datosBrazo[2]);
            aceY2 = int.Parse(datosBrazo[3]);
           
        }
       // Debug.Log("X brazo" + aceZ);
        brazo.transform.eulerAngles = new Vector3(aceY, 0, (aceZ * -1));
        pierna.transform.eulerAngles = new Vector3(aceY2, 0, aceZ2);

        //   transform.eulerAngles = new Vector3(0, 0, (aceZ * -1));

        //Debug.Log("X " + aceZ);
        //Debug.Log("Y "+aceY);

        /*if(aceZ >= -40 && aceZ < -35)
        {
           // Debug.Log("BUZZ");
            puerto.Write("1");
            ganastes.gameObject.SetActive(true);
            brazo.GetComponent<Victoria>().win = true;
        }
        if (mn == true)
        {
            puerto.Write("2");
            //Debug.Log("PERDISTE");
        }
        */
    }

    /*public void moverPierna(string valorPierna)
    {
        string[] datosPierna = valorPierna.Split(char.Parse(","));

        if (datosPierna.Length == 4)
        {
            aceZ2 = int.Parse(datosPierna[2]);
            aceY2 = int.Parse(datosPierna[3]);
        }

        pierna.transform.eulerAngles = new Vector3(0, aceY2, aceZ2);
    }*/
}
