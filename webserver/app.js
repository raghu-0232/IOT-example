const express = require('express');
const mysql = require('mysql2');
const app = express();

// MySQL database configuration
const db_config = {
  host: 'localhost',
  user: 'root',
  password: 'Raghu123@',
  database: 'esp'
};

// Create a MySQL pool
const pool = mysql.createPool(db_config);

// Create a promise-based MySQL connection
const promisePool = pool.promise();

// Serve static files (CSS, JS, etc.)
app.use(express.static('public'));

// Set up a simple route to render the HTML page
app.get('/', (req, res) => {
  res.sendFile(__dirname + '/public/index.html');
});

// Set up an API endpoint to fetch temperature and humidity data
app.get('/api/data', async (req, res) => {
  try {
    // Execute a query to get the latest temperature and humidity
    const [rows, fields] = await promisePool.query(
      'SELECT temp, hum FROM sensor_data ORDER BY timestamp DESC LIMIT 1'
    );

    if (rows.length > 0) {
      // Send the result as JSON
      res.json(rows[0]);
    } else {
      res.status(404).json({ error: 'No data found' });
    }
  } catch (error) {
    console.error('Error fetching data:', error);
    res.status(500).json({ error: 'Internal Server Error' });
  }
});


// Start the server on port 3000
const PORT = 3000;
app.listen(PORT, () => {
  console.log(`Server is running at http://localhost:${PORT}`);
});
