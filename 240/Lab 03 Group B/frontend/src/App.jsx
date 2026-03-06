import { useState, useEffect } from 'react';
import './index.css';

function App() {
  const [games, setGames] = useState([]);
  const [loading, setLoading] = useState(true);

  // Form State
  const [title, setTitle] = useState('');
  const [genre, setGenre] = useState('RPG');
  const [rating, setRating] = useState('');
  const [multiplayer, setMultiplayer] = useState(false);

  const [isSubmitting, setIsSubmitting] = useState(false);

  const API_URL = 'http://localhost:3001/api/games';

  const fetchGames = async () => {
    try {
      const response = await fetch(API_URL);
      const data = await response.json();
      setGames(data);
    } catch (error) {
      console.error('Error fetching games:', error);
    } finally {
      setLoading(false);
    }
  };

  useEffect(() => {
    fetchGames();
  }, []);

  const handleSubmit = async (e) => {
    e.preventDefault();
    if (!title) return;

    setIsSubmitting(true);

    const newGame = {
      title,
      genre,
      rating: rating === '' ? 0 : Number(rating),
      multiplayer
    };

    try {
      const response = await fetch(API_URL, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(newGame)
      });

      if (response.ok) {
        // Reset form
        setTitle('');
        setGenre('RPG');
        setRating('');
        setMultiplayer(false);
        // Refresh list
        fetchGames();
      }
    } catch (error) {
      console.error('Error adding game:', error);
    } finally {
      setIsSubmitting(false);
    }
  };

  return (
    <div className="app-container">
      <header>
        <h1>Nexus Gaming Dashboard</h1>
        <p>Manage your game directory with style and precision</p>
      </header>

      <main className="dashboard">
        <aside className="glass-card">
          <h2 className="section-header">Add New Game</h2>
          <form onSubmit={handleSubmit}>
            <div className="form-group">
              <label>Game Title</label>
              <input
                type="text"
                className="form-control"
                placeholder="e.g. Cyber Realm"
                value={title}
                onChange={(e) => setTitle(e.target.value)}
                required
              />
            </div>

            <div className="form-group">
              <label>Genre</label>
              <select
                className="form-control"
                value={genre}
                onChange={(e) => setGenre(e.target.value)}
              >
                <option value="RPG">RPG</option>
                <option value="FPS">FPS</option>
                <option value="Puzzle">Puzzle</option>
                <option value="Strategy">Strategy</option>
                <option value="Simulation">Simulation</option>
              </select>
            </div>

            <div className="form-group">
              <label>Rating (0-10)</label>
              <input
                type="number"
                className="form-control"
                min="0" max="10"
                step="0.1"
                placeholder="0 - 10"
                value={rating}
                onChange={(e) => setRating(e.target.value)}
              />
            </div>

            <div className="form-group checkbox-group">
              <input
                type="checkbox"
                id="multiplayer"
                checked={multiplayer}
                onChange={(e) => setMultiplayer(e.target.checked)}
              />
              <label htmlFor="multiplayer" style={{ marginBottom: 0, cursor: 'pointer', color: '#cbd5e1' }}>
                Multiplayer Supported
              </label>
            </div>

            <button type="submit" className="btn-primary" disabled={isSubmitting}>
              {isSubmitting ? 'Adding...' : 'Publish Game'}
            </button>
          </form>
        </aside>

        <section>
          <div className="section-header glass-card" style={{ padding: '1rem 1.5rem', marginBottom: '1.5rem' }}>
            <h2>Game Directory</h2>
            <span className="badge">{games.length} Entries</span>
          </div>

          {loading ? (
            <div className="loader-container">
              <div className="spinner"></div>
            </div>
          ) : games.length === 0 ? (
            <div className="glass-card" style={{ textAlign: 'center', color: 'var(--text-secondary)' }}>
              <p>No games found in the directory. Create your first listing!</p>
            </div>
          ) : (
            <div className="games-grid">
              {games.map((game) => (
                <div key={game._id} className="glass-card game-card">
                  <h3 className="game-title">{game.title}</h3>
                  <div className="game-meta">
                    <span className="game-genre">{game.genre}</span>
                    <span className="game-rating">★ {game.rating || 0}/10</span>
                  </div>
                  <div className="game-footer">
                    <div className={`status-indicator ${game.multiplayer ? 'online' : 'offline'}`}></div>
                    {game.multiplayer ? 'Multiplayer Active' : 'Single Player Only'}
                  </div>
                </div>
              ))}
            </div>
          )}
        </section>
      </main>
    </div>
  );
}

export default App;
