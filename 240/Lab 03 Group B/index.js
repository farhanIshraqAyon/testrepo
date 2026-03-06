const express = require('express');
const app = express();

require('dotenv').config();
const PORT = process.env.PORT || 3000;


//middleware
const cors = require('cors');
app.use(cors());
app.use(express.json());


//routes
const gameRoutes = require('./routes/gameRoutes');
const playerRoutes = require('./routes/playerRoutes');
const developerRoutes = require('./routes/developerRoutes');
const collaborationRoutes = require('./routes/collaborationRoutes');

app.use('/api/games', gameRoutes);
app.use('/api/players', playerRoutes);
app.use('/api/developers', developerRoutes);
app.use('/api/collaborations', collaborationRoutes);



//monngodb connection
const mongoose = require('mongoose');
mongoose.connect(process.env.MongoDB_URI).then(() => {
    console.log('Connected to MongoDB');
    app.listen(PORT, () => {
        console.log(`Server is running on http://localhost:${PORT}`);
    });
}).catch((error) => {
    console.error('Error connecting to MongoDB:', error);
});

