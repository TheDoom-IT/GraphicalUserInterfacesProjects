import ReactDOM from 'react-dom/client';
import './index.css';
import App from './App';
import { BrowserRouter, Route, Routes } from 'react-router-dom';
import { PATH_BLOGS, PATH_BLOGS_EDIT, PATH_BLOGS_NEW, PATH_BLOGS_SHOW, PATH_ENTRIES_EDIT, PATH_ENTRIES_NEW, PATH_ENTRIES_SHOW, PATH_FORBIDDEN, PATH_LOGGED_OUT, PATH_LOGIN, PATH_REGISTER, PATH_USER_PROFILE } from './routes/constants';
import { Login } from './routes/login';
import { Register } from './routes/register';
import { Empty } from './routes/empty';
import { MainPage } from './routes/main-page';
import { UserProfile } from './routes/user-profile';
import { Forbidden } from './routes/forbidden';
import { BlogsShow } from './routes/blogs/show';
import { BlogsEdit } from './routes/blogs/edit';
import { BlogsNew } from './routes/blogs/new';
import { EntriesShow } from './routes/entries/show';
import { EntriesEdit } from './routes/entries/edit';
import { EntriesNew } from './routes/entries/new';
import { LoggedOut } from './routes/logged-out';

const root = ReactDOM.createRoot(
  document.getElementById('root') as HTMLElement
);
root.render(
  <BrowserRouter>
    <Routes>
      <Route path="/" element={<App />} >
        <Route index element={<MainPage />} />
        <Route path={PATH_LOGGED_OUT} element={<LoggedOut />} />
        <Route path={PATH_LOGIN} element={<Login />} />
        <Route path={PATH_REGISTER} element={<Register />} />
        <Route path={PATH_USER_PROFILE} element={<UserProfile />} />
        <Route path={PATH_FORBIDDEN} element={<Forbidden />} />
        <Route path={PATH_BLOGS}>
          <Route path={PATH_BLOGS_SHOW} element={<BlogsShow />} />
          <Route path={PATH_BLOGS_EDIT} element={<BlogsEdit />} />
          <Route path={PATH_BLOGS_NEW} element={<BlogsNew />} />
          <Route path={PATH_ENTRIES_SHOW} element={<EntriesShow />} />
          <Route path={PATH_ENTRIES_EDIT} element={<EntriesEdit />} />
          <Route path={PATH_ENTRIES_NEW} element={<EntriesNew />} />
        </Route>
        <Route path="*" element={<Empty />} />
      </Route>
    </Routes>
  </BrowserRouter>
  // TODO: Check if user is logged in every view
);

// If you want to start measuring performance in your app, pass a function
// to log results (for example: reportWebVitals(console.log))
// or send to an analytics endpoint. Learn more: https://bit.ly/CRA-vitals
