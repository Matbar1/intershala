using System.Collections.Generic;
using UnityEngine;

public class GameManager : MonoBehaviour
{
    public GameObject circlePrefab;
    public RectTransform linePrefab;
    public RectTransform canvas;
    public GameObject restartButton;
    private bool isDrawing = false;
    private List<GameObject> circles = new List<GameObject>();
    private RectTransform line;

    private void Start()
    {
        Restart();
    }

    private void Update()
    {
        if (Input.GetMouseButtonDown(0))
        {
            StartDrawing();
        }
        else if (Input.GetMouseButtonUp(0))
        {
            StopDrawing();
        }

        if (isDrawing)
        {
            UpdateLine();
        }
    }

    private void StartDrawing()
    {
        isDrawing = true;
        line = Instantiate(linePrefab, canvas);
        line.GetComponent<LineRenderer>().positionCount = 1;
        line.GetComponent<LineRenderer>().SetPosition(0, Input.mousePosition);
    }

    private void UpdateLine()
    {
        line.GetComponent<LineRenderer>().positionCount++;
        line.GetComponent<LineRenderer>().SetPosition(line.GetComponent<LineRenderer>().positionCount - 1, Input.mousePosition);
    }

    private void StopDrawing()
    {
        isDrawing = false;
        Destroy(line.gameObject);

        foreach (GameObject circle in circles)
        {
            if (IsCircleInsideLine(circle))
            {
                Destroy(circle);
            }
        }
    }

    private bool IsCircleInsideLine(GameObject circle)
    {
        Collider2D circleCollider = circle.GetComponent<Collider2D>();
        Vector3[] linePositions = new Vector3[line.GetComponent<LineRenderer>().positionCount];

        for (int i = 0; i < line.GetComponent<LineRenderer>().positionCount; i++)
        {
            linePositions[i] = line.GetComponent<LineRenderer>().GetPosition(i);
        }

        return circleCollider.OverlapPoint(linePositions[0]) || circleCollider.OverlapPoint(linePositions[linePositions.Length - 1]);
    }

    public void Restart()
    {
        foreach (GameObject circle in circles)
        {
            Destroy(circle);
        }
        circles.Clear();

        int circleCount = Random.Range(5, 11);
        for (int i = 0; i < circleCount; i++)
        {
            Vector3 spawnPosition = new Vector3(Random.Range(-8f, 8f), Random.Range(-4.5f, 4.5f), 0f);
            GameObject newCircle = Instantiate(circlePrefab, spawnPosition, Quaternion.identity);
            circles.Add(newCircle);
        }

        restartButton.SetActive(false);
    }

    public void ShowRestartButton()
    {
        restartButton.SetActive(true);
    }
}
