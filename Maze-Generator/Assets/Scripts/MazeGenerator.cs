/*
	Author: Szymon (sheadovas) Siarkiewicz
	http://szymonsiarkiewicz.pl/

*/


using UnityEngine;
using System.Collections.Generic;


public class MazeGenerator : MonoBehaviour
{
	public int sizeX = 5;
	public int sizeY = 5;

	public float baseWallSize = 1;
	public GameObject prefabWall;
	public GameObject prefabExternalWall;

	private int doubledSizeX;
	private int doubledSizeY;

	private Transform container;
	private Cell[,] cells;


	void Start()
	{
		doubledSizeX = 2 * sizeX;
		doubledSizeY = 2 * sizeY;

		if (prefabWall == null || prefabExternalWall == null)
			Debug.LogError("Nie przypisano prefabu!");

		createMaze();
	}


	public void createMaze()
	{
		container = new GameObject("Walls").transform;
		cells = new Cell[sizeY, sizeX];
		for (int y = 0; y < sizeY; y++)
			for (int x = 0; x < sizeX; x++)
				cells[y, x] = new Cell();
		
		generateGrid();
		generateExternalWalls();
		generateMaze();
	}

	
	void generateGrid()
	{
		for(int y=0;y<sizeY;y++)
		{
			for(int x=0;x<sizeX;x++)
			{
				Vector3 cellPos = new Vector3(x * baseWallSize * 2 - sizeX + 1, y * baseWallSize * 2 - sizeY + 1);
				Vector3 wallPos;

				// ściany prawa-lewa
				if(x < sizeX-1)
				{
					wallPos = new Vector3(baseWallSize, 0, 0) + cellPos;
					GameObject instance = Instantiate(prefabWall, wallPos, Quaternion.identity) as GameObject;
					instance.transform.SetParent(container);

					cells[y, x].right = instance;
				}

				if (x > 0)
				{
					cells[y, x].left = cells[y, x - 1].right;
				}


				// ściany góra-dół
				if (y < sizeY - 1)
				{
					wallPos = new Vector3(0, baseWallSize, 0) + cellPos;
					GameObject instance = Instantiate(prefabWall, wallPos, Quaternion.identity) as GameObject;
					instance.transform.SetParent(container);

					cells[y, x].top = instance;
				}

				if (y > 0)
				{
					cells[y, x].bottom = cells[y-1, x].top;
				}


				// uzupełnienie szachownicy
				if(x < sizeX-1 && y<sizeY - 1)
				{
					wallPos = new Vector3(baseWallSize, baseWallSize, 0) + cellPos;
					GameObject instance = Instantiate(prefabWall, wallPos, Quaternion.identity) as GameObject;
					instance.transform.SetParent(container);
				}
			}
		}
	}


	void generateExternalWalls()
	{
		// ściany poziome
		for(int i=0; i<=doubledSizeX;i++)
		{
			Vector3 pos = new Vector3(i * baseWallSize - sizeX, sizeY, 0);
			GameObject instance = Instantiate(prefabExternalWall, pos, Quaternion.identity) as GameObject;
			instance.transform.SetParent(container);

			pos = new Vector3(i * baseWallSize - sizeX, -sizeY, 0);
			instance = Instantiate(prefabExternalWall, pos, Quaternion.identity) as GameObject;
			instance.transform.SetParent(container);
		}


		// ściany pionowe
		for(int i=0; i< doubledSizeY;i++)
		{
			Vector3 pos = new Vector3(sizeX, i*baseWallSize - sizeY + baseWallSize, 0);
			GameObject instance = Instantiate(prefabExternalWall, pos, Quaternion.identity) as GameObject;
			instance.transform.SetParent(container);

			pos = new Vector3(-sizeX, i * baseWallSize - sizeY + baseWallSize, 0);
			instance = Instantiate(prefabExternalWall, pos, Quaternion.identity) as GameObject;
			instance.transform.SetParent(container);
		}
	}


	void generateMaze()
	{
		int visitedCount = 1;
		int cellsCount = sizeX * sizeY;

		Queue<Vector2> visitedCells = new Queue<Vector2>();
		int x = Random.Range(1, sizeX - 1);
		int y = Random.Range(1, sizeY - 1);

		while(visitedCount < cellsCount)
		{
			string[] possibleDirection = new string[4];
			int possibleDirCount = 0;

			if (x > 0 && !cells[y, x - 1].visited)
				possibleDirection[possibleDirCount++] = "left";

			if (x < sizeX-1 && !cells[y, x + 1].visited)
				possibleDirection[possibleDirCount++] = "right";

			if (y > 0 && !cells[y-1, x].visited)
				possibleDirection[possibleDirCount++] = "bottom";

			if (y < sizeY-1 && !cells[y+1, x].visited)
				possibleDirection[possibleDirCount++] = "top";

			// usuwanie ścian
			if(possibleDirCount != 0)
			{
				string dir = possibleDirection[Random.Range(0, possibleDirCount)];

				if (dir == "left")
				{
					Destroy(cells[y, x].left);
					cells[y, x].visited = true;
					x--;
				}

				else if (dir == "right")
				{
					Destroy(cells[y, x].right);
					cells[y, x].visited = true;
					x++;
				}

				else if (dir == "top")
				{
					Destroy(cells[y, x].top);
					cells[y, x].visited = true;
					y++;
				}

				else if (dir == "bottom")
				{
					Destroy(cells[y, x].bottom);
					cells[y, x].visited = true;
					y--;
				}
				else
					Debug.LogError("Something happened...");

				cells[y, x].visited = true;
				visitedCount++;
				visitedCells.Enqueue(new Vector2(x, y));
			}
			else
			{
				Vector2 retrace = visitedCells.Dequeue();
				x = (int)retrace.x;
				y = (int)retrace.y;
			}
		}
	}
}
