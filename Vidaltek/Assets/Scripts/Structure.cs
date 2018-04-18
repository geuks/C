using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Structure {
    private int i;
    private string[] y;

    [System.Serializable]
    public class Row
    {
        public string Id;
        public string Nom;
        public string Classe;
        public string Description;
        public bool IsTrue = false;
    }

    public string[] GetAllIdfromRow(Row[] x)
    {
        string[] y = new string [x.Length];
        for(i=0;i<x.Length;i++)
        {
            y[i] = x[i].Id;
        }
        return y;
    }

    public string[] GetAllNomfromRow(Row[] x)
    {
        string[] y = new string[x.Length];
        for (i = 0; i < x.Length; i++)
        {
            y[i] = x[i].Nom;
        }
        return y;
    }

    public string[] GetAllClassefromRow(Row[] x)
    {
        string[] y = new string[x.Length];
        for (i = 0; i < x.Length; i++)
        {
            y[i] = x[i].Classe;
        }
        return y;
    }

    public string[] GetAllDescriptionfromRow(Row[] x)
    {
        string[] y = new string[x.Length];
        for (i = 0; i < x.Length; i++)
        {
            y[i] = x[i].Description;
        }
        return y;
    }

    public string GetIdfromRow(Row x)
    {
        return x.Id;
    }

    public string GetNomfromRow(Row x)
    {
        return x.Nom;
    }

    public string GetClassefromRow(Row x)
    {
        return x.Classe;
    }

    public string GetDescriptionfromRow(Row x)
    {
        return x.Description;
    }
}