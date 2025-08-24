package utils

import (
	"encoding/json"
	"os"
)

// LoadJSONFromFile is a generic function that loads and parses JSON data from a file
// into the provided struct type T
func LoadJSONFromFile[T any](filePath string) (*T, error) {
	data, err := os.ReadFile(filePath)
	if err != nil {
		return nil, err
	}
	
	var result T
	err = json.Unmarshal(data, &result)
	if err != nil {
		return nil, err
	}
	
	return &result, nil
}
