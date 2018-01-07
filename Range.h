#pragma once
class Range {
private:
	int min;
	int max;	
	int size;
public:
	Range(int min, int max);

	int GetMin() { return min; }
	void SetMin(int _min) { 
		min = _min;
		size = max - min;
	}

	int GetMax() { return max; }
	void SetMax(int _max) { 
		max = _max;
		size = max - min;
	}

	int GetSize() { return size; }
};	