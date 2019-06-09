SETTINGS = {
    "database": {
        "type": "mongodb",
        "host": "127.0.0.1",
        "port": 27017,
        "password": "",
        "dbname": "bilibili",
        "colname": "videos"
    },
    "spider": {
        "timeout": 10,
        "maxretry": 3,
        "interval": 0.5,
        "maxthread": 32
    }
}
