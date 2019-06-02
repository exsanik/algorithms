typedef vector<vector<pair<int, int>>> matr;
void fordFulkerson(matr& m);
bool findWaySaturation(matr& m, vector<pair<int, int>> &ind, int ver, vector<int> &visited, int &min, int iStart = 1);
bool findWayDistibution(matr& m, vector<pair<int, int>> &ind, int ver, vector<int> &visited, int &min, int iStart = 0);

void fordFulkerson(matr& m)
{
	int min = INT_MAX;
	vector<pair<int, int>> ind;
	vector<int> visited;
	bool res = false;
	do
	{
		ind.clear(); visited.clear(); min = INT_MAX;
		visited.emplace_back(0);
		res = findWaySaturation(m, ind, 0, visited, min);
		for (int i = 0; i < ind.size(); i++)
			m[ind[i].first][ind[i].second].first += min;
	} while (min != INT_MAX );

	do
	{
		ind.clear(); visited.clear(); min = INT_MAX;
		visited.emplace_back(0);
		res = findWayDistibution(m, ind, 0, visited, min);
		for (int i = 0; i < ind.size(); i++)
		{
			if(ind[i].first<0)
				m[-ind[i].first][ind[i].second].first -= min;
			else
				m[ind[i].first][ind[i].second].first += min;
		}
	} while (min != INT_MAX);
}

bool findWaySaturation(matr& m, vector<pair<int, int>> &ind, int ver, vector<int> &visited, int &min, int iStart)
{
	for (int i = iStart; i < m.size(); i++)
	{
		if (ver == m.size() - 1)
			return true;

		int minVer = m[ver][i].second - m[ver][i].first;
		if (minVer == 0)
			continue;
		if (find(visited.begin(), visited.end(), i) == visited.end())
		{
			visited.emplace_back(i);
			if (findWaySaturation(m, ind, i, visited, min) || !ind.empty())
			{
				if (minVer < min)
					min = minVer;
				ind.emplace_back(ver, i);
				return true;
			}
			else
				findWaySaturation(m, ind, ver, visited, min, i + 1);
		}
	}
	return false;
}

bool findWayDistibution(matr& m, vector<pair<int, int>> &ind, int ver, vector<int> &visited, int &min, int iStart)
{
	for (int i = iStart; i < m.size(); i++)
	{
		if (ver == m.size() - 1)
			return true;

		int minVer = m[ver][i].second - m[ver][i].first;
		if (minVer == 0)
			continue;
		if (find(visited.begin(), visited.end(), i) == visited.end())
		{
			visited.emplace_back(i);
			if (findWayDistibution(m, ind, i, visited, min) || !ind.empty())
			{
				if (minVer < min)
					min = minVer;
				ind.emplace_back(ver, i);
				return true;
			}
			else
				findWayDistibution(m, ind, ver, visited, min, i + 1);
		}
	}
	for (int i = iStart; i < m.size(); i++)
	{
		int minVer = m[i][ver].first;
		if (m[i][ver].first == 0)
			continue;
		if (find(visited.begin(), visited.end(), i) == visited.end())
		{
			visited.emplace_back(i);
			if (findWayDistibution(m, ind, i, visited, min) || !ind.empty())
			{
				if (minVer < min)
					min = minVer;
				ind.emplace_back(-i, ver);
				return true;
			}
			else
				findWayDistibution(m, ind, i+1, visited, min, ver);
		}
	}
	return false;
}
