using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Room : MonoBehaviour
{
    public GameObject doorLeft, doorRight, doorUp, doorDown;
    public bool roomLeft, roomRight, roomUp, roomDown;
    public Text text;
    public int stepToStart;
    public int doorNumer;
    void Start()
    {
        doorLeft.SetActive(roomLeft);
        doorRight.SetActive(roomRight);
        doorUp.SetActive(roomUp);
        doorDown.SetActive(roomDown);

    }

    public void UpdateRoom(float x, float y)
    {
        stepToStart = (int)(Mathf.Abs(transform.position.x/x)+Mathf.Abs(transform.position.y/y));
        text.text = stepToStart.ToString();

        if (roomUp)
        {
            doorNumer++;
        }
        if (roomDown)
        {
            doorNumer++;
        }
        if (roomLeft)
        {
            doorNumer++;
        }
        if (roomRight)
        {
            doorNumer++;
        }
    }
}
